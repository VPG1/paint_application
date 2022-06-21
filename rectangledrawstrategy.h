#ifndef RECTANGLEDRAWSTRATEGY_H
#define RECTANGLEDRAWSTRATEGY_H

#include <QImage>
#include <QPainter>
#include "usersettings.h"
#include "drawstrategy.h"

class RectangleDrawStrategy : public DrawStrategy
{
    QImage firstImage;
    QPoint firstPoint;
public:
    RectangleDrawStrategy();

    void press(QMouseEvent *event, QImage *image) override;
    void move(QMouseEvent *event) override;
    void release(QMouseEvent *event) override;

private:
    void drawRectangleTo(QPoint endPoint);
};

#endif // RECTANGLEDRAWSTRATEGY_H
