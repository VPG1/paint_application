#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , userSettings(*(new UserSettings{Qt::black, 10}))
    , scribbleArea(new ScribbleArea(userSettings, this))
{

    ui->setupUi(this);

    setCentralWidget(scribbleArea);

    ui->toolBar->addAction("pen");

    // init change color action
    auto pixmap = QPixmap(colorPixmapSize);
    pixmap.fill(userSettings.color);
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
    userSettings.color = QColorDialog::getColor();
    auto pixmap = QPixmap(colorPixmapSize);
    pixmap.fill(userSettings.color);
    changeColorAction->setIcon(QIcon(pixmap));
}

