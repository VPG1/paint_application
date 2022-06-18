#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->toolBar->addAction("pen");

    // init change color action
    auto pixmap = QPixmap(colorPixmapSize);
    pixmap.fill(selectedColor);
    changeColorAction = new QAction(QIcon(pixmap), "change color");
    connect(changeColorAction, &QAction::triggered, this, &MainWindow::changingColor);
    ui->toolBar->addAction(changeColorAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changingColor()
{
    selectedColor = QColorDialog::getColor();
    auto pixmap = QPixmap(colorPixmapSize);
    pixmap.fill(selectedColor);
    changeColorAction->setIcon(QIcon(pixmap));
}

