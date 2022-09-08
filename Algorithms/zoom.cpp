#include "zoom.h"

Zoom::Zoom() : QObject()
{

}

double Zoom::getCurZoom()
{
    return m_curZoom;
}

QPoint Zoom::getZoomedPoint(const QPoint &point)
{
    return point / m_curZoom;
}

void Zoom::zoomIn()
{
    if(m_curZoom > 5.9){ // если zoom == 8, то ничего не делаем
        return;
    }


    if(m_curZoom < 0.91){ // если zoom < 1, то увеличиваем на 0.1
        m_curZoom += 0.1;
    }
    else if(m_curZoom < 1.9){ // если текущий 1 <= zoom < 2, то увеличиваем на 0.25
        m_curZoom+= 0.25;
    }
    else if(m_curZoom < 5.9){ // если 2 <= zoom < 8, то увеличиваем на 1
        m_curZoom += 1;
    }

    emit zoomChange(m_curZoom);
}

void Zoom::zoomOut()
{
    if(m_curZoom < 0.31){ // если zoom == 0.3, то ничего не делаем
        return;
    }

    if(m_curZoom < 1.1){ // если zoom <= 1, то уменьшаем на 0.1
        m_curZoom -= 0.1;
    }
    else if(m_curZoom < 5.9){ // если 1 < zoom <= 2, то уменьшаем на 0.25
        m_curZoom -= 0.25;
    }
    else if(m_curZoom < 6.1){ // если 2 < zoom <= 8, то уменьшаем на 1
        m_curZoom -= 1;
    }

    emit zoomChange(m_curZoom);
}

void Zoom::wheelZooming(int angleDelta)
{
    double a;
    if(m_curZoom < 1){
        a = double(angleDelta) / 100;
    }
    else{
        a = double(angleDelta) / 20;
    }

    if(angleDelta < 0 && m_curZoom + a < 0.29){
        return;
    }
    else if(angleDelta > 0 && m_curZoom + a > 6.01){
        return;
    }

    m_curZoom += a;

    emit zoomChange(m_curZoom);
}
