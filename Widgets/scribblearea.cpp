#include "scribblearea.h"

ScribbleArea::ScribbleArea(QWidget *parent)
    :  QWidget(parent), m_image(1000, 1000, QImage::Format_RGB32)
{
    m_image.fill(Qt::white);

    // содержимое находится в верхнем левом углу и не изменеяется при изменении размеров окна
    setAttribute(Qt::WA_StaticContents);

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
    painter.drawImage(boudingRect, m_image, boudingRect);
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    // удаляем все состояния канвы следующие за текущим
    if(m_curImage != m_previousStates.end() - 1){
        m_previousStates.assign(m_previousStates.begin(), m_curImage + 1);
    }


    if(event->button() == Qt::LeftButton){
        UserSettings::getInstance()->drawStrategy->press(event, &m_image);

        m_scribbling = true;


        update();
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && m_scribbling){
        UserSettings::getInstance()->drawStrategy->move(event);

        update();
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_scribbling){
        UserSettings::getInstance()->drawStrategy->release(event);

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
