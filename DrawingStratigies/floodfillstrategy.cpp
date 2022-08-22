#include "floodfillstrategy.h"

FloodFillStrategy::FloodFillStrategy()
{

}

void FloodFillStrategy::press(QMouseEvent *event, QImage *image)
{
    floodFill(*image, event->pos(), UserSettings::getInstance()->color);
//    floodFill(ima)
}

void FloodFillStrategy::move(QMouseEvent *)
{
    // ничего не делаем
}

void FloodFillStrategy::release(QMouseEvent *)
{
    // ничего не делаем
}

