#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_scrollArea(new QScrollArea)
    , m_scribbleArea(new ScribbleArea)
{

    ui->setupUi(this);

//    auto scrollArea = new QScrollArea;
//    m_scribbleArea->setFixedSize(1000, 700);
//    m_scribbleArea->setAutoFillBackground(true);
////    m_scribbleArea
//    scrollArea->setWidget(m_scribbleArea);
//    setCentralWidget(m_scribbleArea);
    m_scrollArea = new QScrollArea;
    m_scrollArea->setWidget(m_scribbleArea);
    m_scrollArea->setBackgroundRole(QPalette::Dark);
    m_scrollArea->setWidgetResizable(true);
    setCentralWidget(m_scrollArea);




    // init draw actions

    /*connect(ui->toolBar->addAction("pen"),
            &QAction::triggered, this,  &MainWindow::chosePen);
    connect(ui->toolBar->addAction("line"),
            &QAction::triggered, this, &MainWindow::choseLine);
    connect(ui->toolBar->addAction("rectangle"),
            &QAction::triggered, this, &MainWindow::choseRectangle);
    connect(ui->toolBar->addAction("ellipse"),
            &QAction::triggered, this, &MainWindow::choseEllipse);
    connect(ui->toolBar->addAction("flood fill"),
            &QAction::triggered, this, &MainWindow::choseFloodFill);
    connect(ui->toolBar->addAction("open"),
            &QAction::triggered, this, &MainWindow::open);
    connect(ui->toolBar->addAction("save"),
            &QAction::triggered, this, &MainWindow::save);*/

    QAction* pen = new QAction(this);
    pen->setIcon(QIcon(":/Icons/pencil.png"));
    pen->setIconText("pencil");
    ui->toolBar->addAction(pen);
    connect(pen, &QAction::triggered, this,  &MainWindow::chosePen);
    QCursor cursorPencil = QCursor(QPixmap(":/Icons/pencil_cursor.png"));
    m_scribbleArea->setCursor(cursorPencil);

    //QCursor cursorPencil = QCursor(QPixmap(":/Icons/pencil.png"));
    //ui->toolBar->setCursor(cursorPencil);
    //this->setCursor(cursorPencil);

    QAction* line = new QAction(this);
    line->setIcon(QIcon(":/Icons/line.png"));
    line->setIconText("line");
    ui->toolBar->addAction(line);
    connect(line, &QAction::triggered, this, &MainWindow::choseLine);

    QAction* rectangle = new QAction(this);
    rectangle->setIcon(QIcon(":/Icons/rectangle.png"));
    rectangle->setIconText("rectangle");
    ui->toolBar->addAction(rectangle);
    connect(rectangle, &QAction::triggered, this, &MainWindow::choseRectangle);

    QAction* ellipse = new QAction(this);
    ellipse->setIcon(QIcon(":/Icons/ellipse.png"));
    ellipse->setIconText("ellipse");
    ui->toolBar->addAction(ellipse);
    connect(ellipse, &QAction::triggered, this, &MainWindow::choseEllipse);

    QAction* floodfill = new QAction(this);
    floodfill->setIcon(QIcon(":/Icons/pouring paint.png"));
    floodfill->setIconText("floodfill");
    ui->toolBar->addAction(floodfill);
    connect(floodfill, &QAction::triggered, this, &MainWindow::choseFloodFill);

    QAction* clear = new QAction(this);
    clear->setIcon(QIcon(":/Icons/clear.png"));
    clear->setIconText("clear all");
    ui->toolBar->addAction(clear);
    connect(clear, &QAction::triggered, m_scribbleArea, &ScribbleArea::clear);

    QAction* load = new QAction(tr("&Load"), this);
    QAction* save = new QAction(tr("&Save"), this);
    QAction* info_paint = new QAction(tr("&About Qt Paint"), this);
    QMenu* file = new QMenu(tr("&File"), menuBar());
    QMenu* info = new QMenu(tr("&About"), menuBar());
    menuBar()->addMenu(file);
    menuBar()->addMenu(info);
    file->addAction(load);
    file->addAction(save);
    info->addAction(info_paint);
    connect(load, &QAction::triggered, this, &MainWindow::open);
    connect(save, &QAction::triggered, this, &MainWindow::save);
    connect(info_paint, &QAction::triggered, this, &MainWindow::about);
    load->setShortcut(QKeySequence::Open);
    save->setShortcut(QKeySequence::Save);
    save->setIcon(QPixmap(":/Icons/save.png"));


    // init change color action
    auto pixmap = QPixmap(m_colorPixmapSize);
    pixmap.fill(UserSettings::getInstance()->color);
    m_changeColorAction = new QAction(QIcon(pixmap), "change color");
    connect(m_changeColorAction, &QAction::triggered, this, &MainWindow::changingColor);

    ui->toolBar->addAction(m_changeColorAction);

    // init change pen width action
    ui->toolBar->addWidget(new Slider);


    // intit undo redo actions
    QAction *undoAction = new QAction("undo");
    undoAction->setShortcut(QKeySequence::Undo);
    ui->toolBar->addAction(undoAction);
    undoAction->setIcon(QIcon(":/Icons/undo.png"));
    undoAction->setIconText("undo");
    connect(undoAction, &QAction::triggered, m_scribbleArea, &ScribbleArea::undo);

    QAction *redoAction = new QAction("redo");
    redoAction->setShortcut(QKeySequence::Redo);
    ui->toolBar->addAction(redoAction);
    redoAction->setIcon(QIcon(":/Icons/redo.png"));
    redoAction->setIconText("redo");
    connect(redoAction, &QAction::triggered, m_scribbleArea, &ScribbleArea::redo);

    ui->toolBar->unsetCursor();

    // init zoom in zoom out actions
    QAction *zoomActionIn = new QAction("zoom in");
    zoomActionIn->setShortcut(QKeySequence::ZoomIn);
    ui->toolBar->addAction(zoomActionIn);
    connect(zoomActionIn, &QAction::triggered, m_scribbleArea, &ScribbleArea::zoomIn);

    QAction *zoomActionOut = new QAction("zoom out");
    zoomActionOut->setShortcut(QKeySequence::ZoomOut);
    ui->toolBar->addAction(zoomActionOut);
    connect(zoomActionOut, &QAction::triggered, m_scribbleArea, &ScribbleArea::zoomOut);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changingColor()
{
    UserSettings::getInstance()->color = QColorDialog::getColor();
    auto pixmap = QPixmap(m_colorPixmapSize);
    pixmap.fill(UserSettings::getInstance()->color);
    m_changeColorAction->setIcon(QIcon(pixmap));
}

void MainWindow::chosePen()
{
    UserSettings::getInstance()->drawStrategy = std::make_unique<PenDrawStrategy>();
    QCursor cursorPencil = QCursor(QPixmap(":/Icons/pencil_cursor.png"));
    m_scribbleArea->setCursor(cursorPencil);
}

void MainWindow::choseLine()
{
    UserSettings::getInstance()->drawStrategy = std::make_unique<LineDrawStrategy>();
    m_scribbleArea->unsetCursor();
}

void MainWindow::choseRectangle()
{
    UserSettings::getInstance()->drawStrategy = std::make_unique<RectangleDrawStrategy>();
    m_scribbleArea->unsetCursor();
}

void MainWindow::choseEllipse()
{
    UserSettings::getInstance()->drawStrategy = std::make_unique<EllipseDrawStrategy>();
    m_scribbleArea->unsetCursor();
}

void MainWindow::choseFloodFill()
{
    UserSettings::getInstance()->drawStrategy = std::make_unique<FloodFillStrategy>();
    QCursor cursorFloodFill = QCursor(QPixmap(":/Icons/pouring paint_cursor.png"));
    m_scribbleArea->setCursor(cursorFloodFill);
}


void MainWindow::open()
{
    if (maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(this,
                           tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            m_scribbleArea->openImage(fileName);
    }
}
void MainWindow::save()
{
    //QAction *action = qobject_cast<QAction *>(sender());
    //QByteArray fileFormat = action->data().toByteArray();
    saveFile("png");
}
bool MainWindow::maybeSave()
{
    if (m_scribbleArea->isModified()) {
       QMessageBox::StandardButton res;
       res = QMessageBox::warning(this, tr("PaintApplication"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
                          | QMessageBox::Cancel);
        if (res == QMessageBox::Save)
            return saveFile("png");
        else if (res == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::about()
{
    QMessageBox::StandardButton res = QMessageBox::information(this, tr("PaintApplication"),
                       tr("Application is written in C++, using QT.\n"
                          "Originally made for project in university.\n\n"
                          "Version 1.0.0"),
                       QMessageBox::Ok);
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty())
        return false;
    return m_scribbleArea->saveImage(fileName, fileFormat.constData());
}



