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

    void press(QMouseEvent *event, QImage *image) override;
    void move(QMouseEvent *event) override;
    void release(QMouseEvent *event) override;

private:
    void drawRectangleTo(QPoint endPoint);
};

#endif // RECTANGLEDRAWSTRATEGY_H
