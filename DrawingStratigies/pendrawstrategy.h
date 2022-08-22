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

    void press(QMouseEvent *event, QImage *painter) override;
    void move(QMouseEvent *event) override;
    void release(QMouseEvent *event) override;

    void drawLineTo(QPoint endPoint);
};

#endif // PENDRAWSTRATEGY_H
