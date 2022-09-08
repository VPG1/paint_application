#ifndef ZOOM_H
#define ZOOM_H

#include <QPoint>
#include <QDebug>

class Zoom
{
public:
    Zoom();
    double getCurZoom();
    QPoint getZoomedPoint(const QPoint &point);
    void zoomIn();
    void zoomOut();

    void wheelZooming(int angleDelta);

private:
    double m_curZoom = 1;
};

#endif // ZOOM_H
