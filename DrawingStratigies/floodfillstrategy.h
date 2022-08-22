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

    void press(QMouseEvent *event, QImage *image) override;
    void move(QMouseEvent *event) override;
    void release(QMouseEvent *event) override;
};

#endif // FLOODFILLSTRATEGY_H
