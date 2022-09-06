#include "rectangledrawstrategy.h"

RectangleDrawStrategy::RectangleDrawStrategy()
{

}

void RectangleDrawStrategy::press(QPoint clickedPoint, QImage *image)
{
    m_image = image;
    m_firstImage = m_image->copy();


    m_painter = new QPainter(m_image);
    initPainter();

    m_firstPoint = clickedPoint;
}

void RectangleDrawStrategy::move(QPoint clickedPoint)
{
    m_painter->end();
    *m_image = m_firstImage.copy();

    m_painter->begin(m_image);
    initPainter();

    drawRectangleTo(clickedPoint);
}

void RectangleDrawStrategy::release(QPoint clickedPoint)
{
    drawRectangleTo(clickedPoint);
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

void RectangleDrawStrategy::initPainter()
{
    m_painter->setPen(QPen(UserSettings::getInstance()->color, UserSettings::getInstance()->penWidth, Qt::SolidLine, Qt::RoundCap,
                             Qt::RoundJoin));
//    m_painter->setRenderHint(QPainter::Antialiasing);
}
