#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>
#include <QPainter>
#include "usersettings.h"

namespace Ui {
class Slider;
}

class Slider : public QWidget
{
    Q_OBJECT

public:
    explicit Slider(QWidget *parent = nullptr);
    ~Slider();

private slots:
    void on_verticalSlider_valueChanged(int value);

private:
    Ui::Slider *ui;
};

#endif // SLIDER_H
