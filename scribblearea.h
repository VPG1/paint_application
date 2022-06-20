#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include "usersettings.h"
#include "pendrawstrategy.h"

class ScribbleArea : public QWidget
{
    Q_OBJECT
public:
    ScribbleArea(QWidget *parent = nullptr);
    ~ScribbleArea();
protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

private:
    QImage image; // переменная для хранения рисунка пользователя

    std::unique_ptr<DrawStrategy> drawStrategy;

    QPainter *painter;

//    QPoint lastPoint;
    bool sribbling = false; // происходит ли рисование в данный момент времен

//    void drawLineTo(QPoint endPoint);

private slots:
    void updateAreaSlot(QRect rect);
};

#endif // SCRIBBLEAREA_H
