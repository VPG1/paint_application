#ifndef LINEDRAWSTRATEGY_H
#define LINEDRAWSTRATEGY_H

#include "drawstrategy.h"
#include "usersettings.h"
#include <QPainter>

class LineDrawStrategy : public DrawStrategy
{
    QImage *m_image;
    QPainter *m_painter;

    QPoint m_firstPoint;
    QImage m_firstImage;

public:
    LineDrawStrategy();

    void press(QPoint clickedPoint, QImage *image) override;
    void move(QPoint clickedPoint) override;
    void release(QPoint clickedPoint) override;

private:
    void drawLineTo(QPoint endPoint);
    void initPainter();
};

#endif // LINEDRAWSTRATEGY_H
