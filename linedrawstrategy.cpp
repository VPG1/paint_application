#include "linedrawstrategy.h"

LineDrawStrategy::LineDrawStrategy()
{

}

void LineDrawStrategy::press(QMouseEvent *event, QImage *image)
{
    m_image = image;
    firstImage = m_image->copy();


    m_painter = new QPainter(m_image);
    m_painter->setPen(QPen(UserSettings::getInstance()->color, UserSettings::getInstance()->penWidth, Qt::SolidLine, Qt::RoundCap,
                             Qt::RoundJoin));

    firstPoint = event->pos();
}

void LineDrawStrategy::move(QMouseEvent *event)
{
    m_painter->end();
    *m_image = firstImage.copy();
    m_painter->begin(m_image);

    m_painter->setPen(QPen(UserSettings::getInstance()->color, UserSettings::getInstance()->penWidth, Qt::SolidLine, Qt::RoundCap,
                             Qt::RoundJoin));

    drawLineTo(event->pos());
}

void LineDrawStrategy::release(QMouseEvent *event)
{
    drawLineTo(event->pos());
    m_painter->end();
}

void LineDrawStrategy::drawLineTo(QPoint endPoint)
{
    m_painter->drawLine(firstPoint, endPoint);

    // обновляем область в которой нарисовали линию
    // учитываем penWidth при обновление
//    int rad = (UserSettings::getInstance()->penWidth / 2) + 2;
//    emit updateArea(QRect(firstPoint, endPoint).normalized().adjusted(-rad, -rad, rad, rad));
}
