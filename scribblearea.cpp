#include "scribblearea.h"

ScribbleArea::ScribbleArea(QWidget *parent)
    :  QWidget(parent), image(200, 200, QImage::Format_RGB32), painter(new QPainter(&image))
{
    image.fill(Qt::white);

    // содержимое находится в верхнем левом углу и не изменеяется при изменении размеров окна
    setAttribute(Qt::WA_StaticContents);

    drawStrategy = std::unique_ptr<PenDrawStrategy>(new PenDrawStrategy);

    connect(drawStrategy.get(), &DrawStrategy::updateArea, this, &ScribbleArea::updateAreaSlot);
}

ScribbleArea::~ScribbleArea()
{
    painter->end();
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
//        lastPoint = event->pos();

        painter->setPen(QPen(UserSettings::getInstance()->color, UserSettings::getInstance()->penWidth,
                            Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));

        drawStrategy->press(event, painter);

        sribbling = true;
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && sribbling){
//        drawLineTo(event->pos());
        drawStrategy->move(event);
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && sribbling){
//        drawLineTo(event->pos());
        drawStrategy->release(event);
        sribbling = false;
    }
}

//void ScribbleArea::drawLineTo(QPoint endPoint)
//{
//    QPainter painter(&image);
//    painter.setPen(QPen(UserSettings::getInstance()->color, UserSettings::getInstance()->penWidth,
//                        Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
//    painter.drawLine(lastPoint, endPoint);

//    // обновляем область в которой нарисовали линию
//    // учитываем penWidth при обновление
//    int rad = (UserSettings::getInstance()->penWidth / 2) + 2;
//    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, rad, rad));

//    lastPoint = endPoint;
//}

void ScribbleArea::updateAreaSlot(QRect rect)
{
    update(rect);
}
