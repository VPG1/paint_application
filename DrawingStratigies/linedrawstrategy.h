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

    void press(QMouseEvent *event, QImage *image) override;
    void move(QMouseEvent *event) override;
    void release(QMouseEvent *event) override;

private:
    void drawLineTo(QPoint endPoint);
};

#endif // LINEDRAWSTRATEGY_H
