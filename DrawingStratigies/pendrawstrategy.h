#ifndef PENDRAWSTRATEGY_H
#define PENDRAWSTRATEGY_H

#include "drawstrategy.h"
#include "usersettings.h"
#include <QPainter>

class PenDrawStrategy : public DrawStrategy
{
    QImage *m_image;
    QPainter *m_painter;

    QPoint m_lastPoint;
public:
    PenDrawStrategy();

    void press(QPoint clickedPoint, QImage *painter) override;
    void move(QPoint clickedPoint) override;
    void release(QPoint clickedPoint) override;

private:
    void drawLineTo(QPoint endPoint);

    void initPainter();
};

#endif // PENDRAWSTRATEGY_H
