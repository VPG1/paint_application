#include "ellipsedrawstrategy.h"

EllipseDrawStrategy::EllipseDrawStrategy()
{

}

void EllipseDrawStrategy::press(QPoint clickedPoint, QImage *image)
{
    m_image = image;
    m_firstImage = m_image->copy();


    m_painter = new QPainter(m_image);

    initPainter();

    m_firstPoint = clickedPoint;
}

void EllipseDrawStrategy::move(QPoint clickedPoint)
{
    m_painter->end();
    *m_image = m_firstImage.copy();

    m_painter->begin(m_image);
    initPainter();

    drawEllepse(clickedPoint);
}

void EllipseDrawStrategy::release(QPoint clickedPoint)
{
    drawEllepse(clickedPoint);
    m_painter->end();
}

void EllipseDrawStrategy::drawEllepse(QPoint endPoint)
{
    m_painter->drawEllipse(QRect(m_firstPoint, endPoint));
}

void EllipseDrawStrategy::initPainter()
{
    m_painter->setPen(QPen(UserSettings::getInstance()->color, UserSettings::getInstance()->penWidth, Qt::SolidLine, Qt::RoundCap,
                             Qt::RoundJoin));
    m_painter->setRenderHint(QPainter::Antialiasing);
}
