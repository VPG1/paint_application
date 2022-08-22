#ifndef DRAWSTRATEGY_H
#define DRAWSTRATEGY_H

#include <QMouseEvent>

class DrawStrategy{

public:
    DrawStrategy() = default;
    virtual ~DrawStrategy(){}

    virtual void press(QMouseEvent *event, QImage *image) = 0;
    virtual void move(QMouseEvent *event) = 0;
    virtual void release(QMouseEvent *event) = 0;
};

#endif // DRAWSTRATEGY_H
