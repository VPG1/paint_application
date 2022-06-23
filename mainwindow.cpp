#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scribbleArea(new ScribbleArea(this))
{

    ui->setupUi(this);

    setCentralWidget(scribbleArea);

    connect(ui->toolBar->addAction("pen"),
            &QAction::triggered, this,  &MainWindow::chosePen);
    connect(ui->toolBar->addAction("line"),
            &QAction::triggered, this, &MainWindow::choseLine);
    connect(ui->toolBar->addAction("rectangle"),
            &QAction::triggered, this, &MainWindow::choseRectangle);
    connect(ui->toolBar->addAction("ellipse"),
            &QAction::triggered, this, &MainWindow::choseEllipse);
    connect(ui->toolBar->addAction("flood fill"),
            &QAction::triggered, this, &MainWindow::choseFloodFill);




    // init change color action
    auto pixmap = QPixmap(colorPixmapSize);
    pixmap.fill(UserSettings::getInstance()->color);
    changeColorAction = new QAction(QIcon(pixmap), "change color");
    connect(changeColorAction, &QAction::triggered, this, &MainWindow::changingColor);

    ui->toolBar->addAction(changeColorAction);

    // init change pen width action
    ui->toolBar->addWidget(new Slider);


    QAction *undoAction = new QAction("undo");
    undoAction->setShortcut(QKeySequence::Undo);
    ui->toolBar->addAction(undoAction);
    connect(undoAction, &QAction::triggered, scribbleArea, &ScribbleArea::undo);

    QAction *redoAction = new QAction("redo");
    redoAction->setShortcut(QKeySequence::Redo);
    ui->toolBar->addAction(redoAction);
    connect(redoAction, &QAction::triggered, scribbleArea, &ScribbleArea::redo);
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

void MainWindow::chosePen()
{
    UserSettings::getInstance()->drawStrategy = std::make_unique<PenDrawStrategy>();
}

void MainWindow::choseLine()
{
    UserSettings::getInstance()->drawStrategy = std::make_unique<LineDrawStrategy>();
}

void MainWindow::choseRectangle()
{
    UserSettings::getInstance()->drawStrategy = std::make_unique<RectangleDrawStrategy>();
}

void MainWindow::choseEllipse()
{
    UserSettings::getInstance()->drawStrategy = std::make_unique<EllipseDrawStrategy>();
}

void MainWindow::choseFloodFill()
{
    UserSettings::getInstance()->drawStrategy = std::make_unique<FloodFillStrategy>();
}

