#ifndef DRAWSTRATEGY_H
#define DRAWSTRATEGY_H

#include <QMouseEvent>

class DrawStrategy{

public:
    DrawStrategy() = default;
    virtual ~DrawStrategy(){}

    virtual void press(QPoint clickedPoint, QImage *image) = 0;
    virtual void move(QPoint clickedPoint) = 0;
    virtual void release(QPoint clickedPoint) = 0;
};

#endif // DRAWSTRATEGY_H
