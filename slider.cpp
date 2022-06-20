#include "slider.h"
#include "ui_slider.h"

Slider::Slider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Slider)
{
    ui->setupUi(this);

    ui->verticalSlider->setValue(UserSettings::getInstance()->penWidth);

    QPixmap pixmap(100, UserSettings::getInstance()->penWidth);
    pixmap.fill(Qt::black);
    ui->label->setPixmap(pixmap);

    ui->label_2->setText(QString::number(UserSettings::getInstance()->penWidth));
}

Slider::~Slider()
{
    delete ui;
}

void Slider::on_verticalSlider_valueChanged(int value)
{
    UserSettings::getInstance()->penWidth = value;

    QPixmap pixmap(100, value);
    pixmap.fill(Qt::black);

    ui->label->setPixmap(pixmap);
    ui->label_2->setText(QString::number(value));
}

