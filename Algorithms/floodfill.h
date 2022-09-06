#ifndef FLOODFILL_H
#define FLOODFILL_H

#include <QImage>
#include <QPoint>
#include <QPainter>
#include <deque>
#include <QApplication>

void floodFill(QImage& image, QPoint seed, QColor newColor);


#endif // FLOODFILL_H
