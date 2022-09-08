#include "scribblearea.h"

ScribbleArea::ScribbleArea(QWidget *parent)
    :  QWidget(parent), m_image(m_imageWidth, m_imageHeight, QImage::Format_ARGB32_Premultiplied)
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

    double zoom = UserSettings::getInstance()->zoom->getCurZoom();
    QImage zoomedImage = m_image.scaled(m_image.width() * zoom, m_image.height() * zoom, Qt::KeepAspectRatio);

    setMinimumSize(m_imageWidth * zoom + 10, m_imageHeight * zoom + 10);

    painter.drawImage(5, 5, zoomedImage);
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    // удаляем все состояния канвы следующие за текущим
    if(m_curImage != m_previousStates.end() - 1){
        m_previousStates.assign(m_previousStates.begin(), m_curImage + 1);
    }


    if(event->button() == Qt::LeftButton){
        // рисуем с учетом zoom-а
        UserSettings::getInstance()->drawStrategy->press(UserSettings::getInstance()->zoom->getZoomedPoint(event->pos()), &m_image);

        m_scribbling = true;

        // перерисовываем
        update();
    }

}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && m_scribbling){
        // рисуем с учетом zoom-а
        UserSettings::getInstance()->drawStrategy->move(UserSettings::getInstance()->zoom->getZoomedPoint(event->pos()));

        // перерисовываем
        update();
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_scribbling){
        // рисуем с учетом zoom-а
        UserSettings::getInstance()->drawStrategy->release(UserSettings::getInstance()->zoom->getZoomedPoint(event->pos()));

        m_scribbling = false;
        modified = true;

        // перерисовываем
        update();


        // сохраняем в m_previousState для undo redo
        m_previousStates.push_back(m_image.copy());
        ++m_curImage;

        // в случае если кол-во предыдущих состаяний канвы > 50 то удаляем самое ранее сохраненное действие
        if(m_previousStates.size() >= 51){
            m_previousStates.pop_front();
        }
    }
}

void ScribbleArea::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers() & Qt::ControlModifier){
        QPoint numDegrees = event->angleDelta() / 8;
        if (!numDegrees.isNull()) {
            UserSettings::getInstance()->zoom->wheelZooming(numDegrees.y());
        }
        update();
    }
    else{
        QWidget::wheelEvent(event);
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
    UserSettings::getInstance()->zoom->zoomIn();
    qDebug() << UserSettings::getInstance()->zoom->getCurZoom();
    update();
}

void ScribbleArea::zoomOut()
{
    UserSettings::getInstance()->zoom->zoomOut();
    qDebug() << UserSettings::getInstance()->zoom->getCurZoom();
    update();
}
