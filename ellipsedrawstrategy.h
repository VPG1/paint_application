#ifndef ELLIPSEDRAWSTRATEGY_H
#define ELLIPSEDRAWSTRATEGY_H

#include <QPainter>
#include <QImage>
#include "drawstrategy.h"
#include "usersettings.h"

class EllipseDrawStrategy : public DrawStrategy
{
    QImage firstImage;
    QPoint firstPoint;

public:
    EllipseDrawStrategy();

    void press(QMouseEvent *event, QImage *image) override;
    void move(QMouseEvent *event) override;
    void release(QMouseEvent *event) override;

private:
    void drawEllepse(QPoint endPoint);
};

#endif // ELLIPSEDRAWSTRATEGY_H
