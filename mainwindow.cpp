#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scribbleArea(new ScribbleArea(this))
{

    ui->setupUi(this);

    setCentralWidget(scribbleArea);

    ui->toolBar->addAction("pen");

    // init change color action
    auto pixmap = QPixmap(colorPixmapSize);
    pixmap.fill(UserSettings::getInstance()->color);
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
    UserSettings::getInstance()->color = QColorDialog::getColor();
    auto pixmap = QPixmap(colorPixmapSize);
    pixmap.fill(UserSettings::getInstance()->color);
    changeColorAction->setIcon(QIcon(pixmap));
}

