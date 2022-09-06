#include "linedrawstrategy.h"

LineDrawStrategy::LineDrawStrategy()
{

}

void LineDrawStrategy::press(QPoint clickedPoint, QImage *image)
{
    m_image = image;
    m_firstImage = m_image->copy();


    m_painter = new QPainter(m_image);
    initPainter();

    m_firstPoint = clickedPoint;
}

void LineDrawStrategy::move(QPoint clickedPoint)
{
    m_painter->end();

    *m_image = m_firstImage.copy();

    m_painter->begin(m_image);
    initPainter();

    drawLineTo(clickedPoint);
}

void LineDrawStrategy::release(QPoint clickedPoint)
{
    drawLineTo(clickedPoint);
    m_painter->end();
}

void LineDrawStrategy::drawLineTo(QPoint endPoint)
{
    m_painter->drawLine(m_firstPoint, endPoint);

    // обновляем область в которой нарисовали линию
    // учитываем penWidth при обновление
//    int rad = (UserSettings::getInstance()->penWidth / 2) + 2;
//    emit updateArea(QRect(firstPoint, endPoint).normalized().adjusted(-rad, -rad, rad, rad));
}

void LineDrawStrategy::initPainter()
{
    m_painter->setPen(QPen(UserSettings::getInstance()->color, UserSettings::getInstance()->penWidth, Qt::SolidLine, Qt::RoundCap,
                             Qt::RoundJoin));
//    m_painter->setRenderHint(QPainter::Antialiasing);
}
