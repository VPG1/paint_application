#ifndef ZOOM_H
#define ZOOM_H

#include <QPoint>
#include <QDebug>
#include <QObject>

class Zoom : public QObject
{
    Q_OBJECT
public:
    Zoom();
    double getCurZoom();
    QPoint getZoomedPoint(const QPoint &point);
    void zoomIn();
    void zoomOut();

    void wheelZooming(int angleDelta);

signals:
    void zoomChange(double newZoom);

private:
    double m_curZoom = 1;
};

#endif // ZOOM_H
