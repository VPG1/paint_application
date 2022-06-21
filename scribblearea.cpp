#include "scribblearea.h"

ScribbleArea::ScribbleArea(QWidget *parent)
    :  QWidget(parent), image(1000, 1000, QImage::Format_RGB32)
{
    image.fill(Qt::white);

    // содержимое находится в верхнем левом углу и не изменеяется при изменении размеров окна
    setAttribute(Qt::WA_StaticContents);

//    drawStrategy = std::unique_ptr<RectangleDrawStrategy>(new RectangleDrawStrategy);

//    connect(UserSettings::getInstance()->drawStrategy.get(), &DrawStrategy::updateArea, this, &ScribbleArea::updateAreaSlot);
}

ScribbleArea::~ScribbleArea()
{
}

void ScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect boudingRect = event->rect(); // область которую нужно перерисовать
    painter.drawImage(boudingRect, image, boudingRect);
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){

        UserSettings::getInstance()->drawStrategy->press(event, &image);

        sribbling = true;

        update();
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && sribbling){
        UserSettings::getInstance()->drawStrategy->move(event);

        update();
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && sribbling){
        UserSettings::getInstance()->drawStrategy->release(event);

        sribbling = false;

        update();
    }
}

void ScribbleArea::updateAreaSlot(QRect rect)
{
    update(rect);
}
