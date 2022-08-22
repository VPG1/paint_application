#include "pendrawstrategy.h"

PenDrawStrategy::PenDrawStrategy() : DrawStrategy()
{}

void PenDrawStrategy::press(QMouseEvent *event, QImage *image)
{
    m_image = image;

    m_painter = new QPainter(image);
    m_painter->setPen(QPen(UserSettings::getInstance()->color, UserSettings::getInstance()->penWidth, Qt::SolidLine, Qt::RoundCap,
                             Qt::RoundJoin));

    m_lastPoint = event->pos();

}

void PenDrawStrategy::move(QMouseEvent *event)
{
    drawLineTo(event->pos());
}

void PenDrawStrategy::release(QMouseEvent *event)
{
    drawLineTo(event->pos());

    m_painter->end();
}

void PenDrawStrategy::drawLineTo(QPoint endPoint)
{
    m_painter->drawLine(m_lastPoint, endPoint);

    // обновляем область в которой нарисовали линию
    // учитываем penWidth при обновление
//    int rad = (UserSettings::getInstance()->penWidth / 2) + 2;
//    emit updateArea(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, rad, rad));

    m_lastPoint = endPoint;
}
