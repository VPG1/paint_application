#include "scribblearea.h"

ScribbleArea::ScribbleArea(UserSettings &userSetting, QWidget *parent)
    :  QWidget(parent), image(200, 200, QImage::Format_RGB32), userSettings(userSetting)
{
    image.fill(Qt::white);
    // содержимое находится в верхнем левом углу и не изменеяется при изменении размеров окна
    setAttribute(Qt::WA_StaticContents);
}

void ScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect boudingRect = event->rect(); // область которую нужно перерисовать
    painter.drawImage(boudingRect, image, boudingRect);
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        lastPoint = event->pos();
        sribbling = true;
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && sribbling){
        drawLineTo(event->pos());
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && sribbling){
        drawLineTo(event->pos());
        sribbling = false;
    }
}

void ScribbleArea::drawLineTo(QPoint endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(userSettings.color, userSettings.penWidth,
                        Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);

    // обновляем область в которой нарисовали линию
    // учитываем penWidth при обновление
    int rad = (userSettings.penWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, rad, rad));

    lastPoint = endPoint;
}
