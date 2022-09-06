#include "scribblearea.h"

ScribbleArea::ScribbleArea(QWidget *parent)
    :  QWidget(parent), m_image(m_imageWidth, m_imageHeight, QImage::Format_RGB32)
{
    m_image.fill(Qt::white);

//    setFixedSize(m_imageWidth, m_imageHeight);

    // содержимое находится в верхнем левом углу и не изменеяется при изменении размеров окна
//    setAttribute(Qt::WA_StaticContents);

    setMinimumSize(m_imageWidth + 10, m_imageHeight + 10);

    m_previousStates.push_back(m_image.copy());
    m_curImage = m_previousStates.begin();

//    drawStrategy = std::unique_ptr<RectangleDrawStrategy>(new RectangleDrawStrategy);

//    connect(UserSettings::getInstance()->drawStrategy.get(), &DrawStrategy::updateArea, this, &ScribbleArea::updateAreaSlot);
}

ScribbleArea::~ScribbleArea()
{
}
bool ScribbleArea::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;
    //QSize newSize = loadedImage.size().expandedTo(size());
    QSize def(1000, 1000);
    QSize newSize = loadedImage.size();
    if (newSize.height() <= def.height() && newSize.width() <= def.width()){
        resizeImage(&loadedImage, def);
    }
    else if (newSize.height() > def.height() && newSize.width() > def.width()){
        QSize diff = newSize - def;\
        QSize bas(200, 200);
        newSize += diff;
        newSize += bas;
        resizeImage(&loadedImage, newSize);
    }
    m_image = loadedImage;
    modified = false;
    update();
    return true;
}

bool ScribbleArea::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = m_image;
    //resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    }
    return false;
}
void ScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect boudingRect = event->rect(); // область которую нужно перерисовать

    double zoom = UserSettings::getInstance()->zoom;
    QImage zoomedImage = m_image.scaled(m_image.width() * zoom, m_image.height() * zoom, Qt::KeepAspectRatio);

    setMinimumSize(m_imageWidth * zoom + 10, m_imageHeight * zoom + 10);

    painter.drawImage(5, 5, zoomedImage);
//    painter.drawImage(boudingRect, zoomedImage, boudingRect);
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    // удаляем все состояния канвы следующие за текущим
    if(m_curImage != m_previousStates.end() - 1){
        m_previousStates.assign(m_previousStates.begin(), m_curImage + 1);
    }


    if(event->button() == Qt::LeftButton){
//        int verticalOffset = UserSettings::getInstance()->verticalOffset;
//        int horizontalOffset = UserSettings::getInstance()->horizontalOffset;
        double zoom = UserSettings::getInstance()->zoom;
        QPoint clickedPoint(event->pos().x() / zoom, event->pos().y() / zoom);

        qDebug() << clickedPoint << event->pos();

        UserSettings::getInstance()->drawStrategy->press(clickedPoint, &m_image);

        m_scribbling = true;

        update();
    }

}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && m_scribbling){
        double zoom = UserSettings::getInstance()->zoom;
        QPoint clickedPoint(double(event->pos().x()) / zoom, double(event->pos().y()) / zoom);


        UserSettings::getInstance()->drawStrategy->move(clickedPoint);

        update();
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_scribbling){
        double zoom = UserSettings::getInstance()->zoom;
        QPoint clickedPoint(event->pos().x() / zoom, event->pos().y() / zoom);

        UserSettings::getInstance()->drawStrategy->release(clickedPoint);

        m_scribbling = false;
        modified = true;

        update();


        m_previousStates.push_back(m_image.copy());

        ++m_curImage;
        if(m_previousStates.size() >= 51){
            m_previousStates.pop_front();
        }
    }
}
void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
void ScribbleArea::updateAreaSlot(QRect rect)
{
    update(rect);
}

void ScribbleArea::undo()
{
    // если есть предыдущие состояние канвы и в данный момент не рисуем то делаем undo
    if(m_curImage != m_previousStates.begin() && !m_scribbling){
        --m_curImage;
        m_image = m_curImage->copy();
        update();
    }
}

void ScribbleArea::redo()
{
    // если есть следущие состояние канвы и в данный момент не рисуем то делаем redo
    if(m_curImage != m_previousStates.end() - 1 && !m_scribbling){
        ++m_curImage;
        m_image = m_curImage->copy();
        update();
    }
}

void ScribbleArea::clear()
{
     m_image.fill(Qt::white);
     update();
}

void ScribbleArea::zoomIn()
{
    double curZoom =  UserSettings::getInstance()->zoom;

    if(curZoom > 7.9){ // если zoom == 8, то ничего не делаем
        return;
    }

    if(curZoom < 0.91){ // если zoom < 1, то увеличиваем на 0.1
        UserSettings::getInstance()->zoom += 0.1;
    }
    else if(curZoom < 1.9){ // если текущий 1 <= zoom < 2, то увеличиваем на 0.25
        UserSettings::getInstance()->zoom += 0.25;
    }
    else if(UserSettings::getInstance()->zoom < 7.9){ // если 2 <= zoom < 8, то увеличиваем на 1
        UserSettings::getInstance()->zoom += 1;
    }
    qDebug() << UserSettings::getInstance()->zoom;

    update();
}

void ScribbleArea::zoomOut()
{
    double curZoom =  UserSettings::getInstance()->zoom;

    if(curZoom < 0.31){ // если zoom == 0.3, то ничего не делаем
        return;
    }

    if(curZoom < 1.1){ // если zoom <= 1, то уменьшаем на 0.1
        UserSettings::getInstance()->zoom -= 0.1;
    }
    else if(curZoom < 1.9){ // если 1 < zoom <= 2, то уменьшаем на 0.25
        UserSettings::getInstance()->zoom -= 0.25;
    }
    else if(curZoom < 8.1){ // если 2 < zoom <= 8, то уменьшаем на 1
        UserSettings::getInstance()->zoom -= 1;
    }
    qDebug() << UserSettings::getInstance()->zoom;

    update();
}
