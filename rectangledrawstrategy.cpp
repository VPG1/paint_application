#include "rectangledrawstrategy.h"

RectangleDrawStrategy::RectangleDrawStrategy()
{

}

void RectangleDrawStrategy::press(QMouseEvent *event, QImage *image)
{
    m_image = image;
    firstImage = m_image->copy();


    m_painter = new QPainter(m_image);
    m_painter->setPen(QPen(UserSettings::getInstance()->color, UserSettings::getInstance()->penWidth, Qt::SolidLine, Qt::RoundCap,
                             Qt::RoundJoin));

    firstPoint = event->pos();
}

void RectangleDrawStrategy::move(QMouseEvent *event)
{
    m_painter->end();
    *m_image = firstImage.copy();
    m_painter->begin(m_image);

    m_painter->setPen(QPen(UserSettings::getInstance()->color, UserSettings::getInstance()->penWidth, Qt::SolidLine, Qt::RoundCap,
                             Qt::RoundJoin));

    drawRectangleTo(event->pos());
}

void RectangleDrawStrategy::release(QMouseEvent *event)
{
    drawRectangleTo(event->pos());
    m_painter->end();
}

void RectangleDrawStrategy::drawRectangleTo(QPoint endPoint)
{
    m_painter->drawRect(QRect(firstPoint, endPoint));

    // обновляем область в которой нарисовали линию
    // учитываем penWidth при обновление
//    int rad = (UserSettings::getInstance()->penWidth / 2) + 2;
//    emit updateArea(QRect(firstPoint, endPoint).normalized().adjusted(-rad, -rad, rad, rad));
//    emit updateArea(QRect(0, 0, 1000, 1000));
}
