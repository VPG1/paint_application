#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include "usersettings.h"

class ScribbleArea : public QWidget
{
    Q_OBJECT
public:
    ScribbleArea(UserSettings &userSetting, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

private:
    QImage image; // переменная для хранения рисунка пользователя

    QPoint lastPoint;
    bool sribbling = false; // происходит ли рисование в данный момент времени

    UserSettings &userSettings;

    void drawLineTo(QPoint endPoint);
};

#endif // SCRIBBLEAREA_H
