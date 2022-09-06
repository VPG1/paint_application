#ifndef ELLIPSEDRAWSTRATEGY_H
#define ELLIPSEDRAWSTRATEGY_H

#include <QPainter>
#include <QImage>
#include "drawstrategy.h"
#include "usersettings.h"

class EllipseDrawStrategy : public DrawStrategy
{
    QImage *m_image;
    QPainter *m_painter;

    QImage m_firstImage;
    QPoint m_firstPoint;

public:
    EllipseDrawStrategy();

    void press(QPoint clickedPoint, QImage *image) override;
    void move(QPoint clickedPoint) override;
    void release(QPoint clickedPoint) override;

private:
    void drawEllepse(QPoint endPoint);

    void initPainter();
};

#endif // ELLIPSEDRAWSTRATEGY_H
