#include "floodfillstrategy.h"

FloodFillStrategy::FloodFillStrategy()
{

}

void FloodFillStrategy::press(QPoint clickedPoint, QImage *image)
{
    floodFill(*image, clickedPoint, UserSettings::getInstance()->color);
//    floodFill(ima)
}

void FloodFillStrategy::move(QPoint)
{
    // ничего не делаем
}

void FloodFillStrategy::release(QPoint)
{
    // ничего не делаем
}

