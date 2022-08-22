#include "rectangledrawstrategy.h"

RectangleDrawStrategy::RectangleDrawStrategy()
{

}

void RectangleDrawStrategy::press(QMouseEvent *event, QImage *image)
{
    m_image = image;
    m_firstImage = m_image->copy();


    m_painter = new QPainter(m_image);
    m_painter->setPen(QPen(UserSettings::getInstance()->color, UserSettings::getInstance()->penWidth, Qt::SolidLine, Qt::RoundCap,
                             Qt::RoundJoin));

    m_firstPoint = event->pos();
}

void RectangleDrawStrategy::move(QMouseEvent *event)
{
    m_painter->end();
    *m_image = m_firstImage.copy();
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
    m_painter->drawRect(QRect(m_firstPoint, endPoint));

    // обновляем область в которой нарисовали линию
    // учитываем penWidth при обновление
//    int rad = (UserSettings::getInstance()->penWidth / 2) + 2;
//    emit updateArea(QRect(firstPoint, endPoint).normalized().adjusted(-rad, -rad, rad, rad));
//    emit updateArea(QRect(0, 0, 1000, 1000));
}
