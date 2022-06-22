#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include "usersettings.h"
#include "pendrawstrategy.h"
#include "linedrawstrategy.h"
#include "rectangledrawstrategy.h"

class ScribbleArea : public QWidget
{
    Q_OBJECT
public:
    ScribbleArea(QWidget *parent = nullptr);
    ~ScribbleArea();
    void clearImage();
protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

private:
    QImage image; // переменная для хранения рисунка пользователя

    bool sribbling = false; // происходит ли рисование в данный момент времен

private slots:
    void updateAreaSlot(QRect rect);
};

#endif // SCRIBBLEAREA_H
