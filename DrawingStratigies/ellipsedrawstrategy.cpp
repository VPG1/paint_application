#include "ellipsedrawstrategy.h"

EllipseDrawStrategy::EllipseDrawStrategy()
{

}

void EllipseDrawStrategy::press(QMouseEvent *event, QImage *image)
{
    m_image = image;
    m_firstImage = m_image->copy();


    m_painter = new QPainter(m_image);
    m_painter->setPen(QPen(UserSettings::getInstance()->color, UserSettings::getInstance()->penWidth, Qt::SolidLine, Qt::RoundCap,
                             Qt::RoundJoin));

    m_firstPoint = event->pos();
}

void EllipseDrawStrategy::move(QMouseEvent *event)
{
    m_painter->end();
    *m_image = m_firstImage.copy();
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
    m_painter->drawEllipse(QRect(m_firstPoint, endPoint));
}
