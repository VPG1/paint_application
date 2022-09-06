#ifndef FLOODFILLSTRATEGY_H
#define FLOODFILLSTRATEGY_H

#include <QMouseEvent>
#include "drawstrategy.h"
#include "usersettings.h"
#include "floodfill.h"

class FloodFillStrategy : public DrawStrategy
{
public:
    FloodFillStrategy();

    void press(QPoint clickedPoint, QImage *image) override;
    void move(QPoint clickedPoint) override;
    void release(QPoint clickedPoint) override;
};

#endif // FLOODFILLSTRATEGY_H
