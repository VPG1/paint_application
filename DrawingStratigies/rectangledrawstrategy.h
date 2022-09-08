#ifndef RECTANGLEDRAWSTRATEGY_H
#define RECTANGLEDRAWSTRATEGY_H

#include <QImage>
#include <QPainter>
#include "usersettings.h"
#include "drawstrategy.h"

class RectangleDrawStrategy : public DrawStrategy
{
    QImage *m_image;
    QPainter *m_painter;

    QImage m_firstImage;
    QPoint m_firstPoint;
public:
    RectangleDrawStrategy();

    void press(QPoint clickedPoint, QImage *image) override;
    void move(QPoint clickedPoint) override;
    void release(QPoint clickedPoint) override;

private:
    void drawRectangleTo(QPoint endPoint);
    void initPainter();
};

#endif // RECTANGLEDRAWSTRATEGY_H
