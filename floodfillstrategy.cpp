#include "floodfillstrategy.h"

FloodFillStrategy::FloodFillStrategy()
{

}

void FloodFillStrategy::press(QMouseEvent *event, QImage *image)
{
    floodFill(*image, event->pos(), UserSettings::getInstance()->color);
//    floodFill(ima)
}

void FloodFillStrategy::move(QMouseEvent *event)
{
    // ничего не делаем
}

void FloodFillStrategy::release(QMouseEvent *event)
{
    // ничего не делаем
}
