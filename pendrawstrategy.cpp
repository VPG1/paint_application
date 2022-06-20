#include "pendrawstrategy.h"

PenDrawStrategy::PenDrawStrategy() : DrawStrategy()
{}

void PenDrawStrategy::press(QMouseEvent *event, QPainter *painter)
{
    m_painter = painter;
    lastPoint = event->pos();
}

void PenDrawStrategy::move(QMouseEvent *event)
{
    drawLineTo(event->pos());
}

void PenDrawStrategy::release(QMouseEvent *event)
{
    drawLineTo(event->pos());
}

void PenDrawStrategy::drawLineTo(QPoint endPoint)
{
    m_painter->drawLine(lastPoint, endPoint);

    // обновляем область в которой нарисовали линию
    // учитываем penWidth при обновление
    int rad = (UserSettings::getInstance()->penWidth / 2) + 2;
    emit updateArea(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, rad, rad));

    lastPoint = endPoint;
}
