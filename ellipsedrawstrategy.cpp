#include "ellipsedrawstrategy.h"

EllipseDrawStrategy::EllipseDrawStrategy()
{

}

void EllipseDrawStrategy::press(QMouseEvent *event, QImage *image)
{
    m_image = image;
    firstImage = m_image->copy();


    m_painter = new QPainter(m_image);
    m_painter->setPen(QPen(UserSettings::getInstance()->color, UserSettings::getInstance()->penWidth, Qt::SolidLine, Qt::RoundCap,
                             Qt::RoundJoin));

    firstPoint = event->pos();
}

void EllipseDrawStrategy::move(QMouseEvent *event)
{
    m_painter->end();
    *m_image = firstImage.copy();
    m_painter->begin(m_image);

    m_painter->setPen(QPen(UserSettings::getInstance()->color, UserSettings::getInstance()->penWidth, Qt::SolidLine, Qt::RoundCap,
                             Qt::RoundJoin));

    drawEllepse(event->pos());
}

void EllipseDrawStrategy::release(QMouseEvent *event)
{
    drawEllepse(event->pos());
    m_painter->end();
}

void EllipseDrawStrategy::drawEllepse(QPoint endPoint)
{
    m_painter->drawEllipse(QRect(firstPoint, endPoint));
}
