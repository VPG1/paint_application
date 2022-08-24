#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_scribbleArea(new ScribbleArea(this))
{

    ui->setupUi(this);

    setCentralWidget(m_scribbleArea);

    // init draw actions
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
    connect(ui->toolBar->addAction("clear"), &QAction::triggered, m_scribbleArea, &ScribbleArea::clear);

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
    connect(undoAction, &QAction::triggered, m_scribbleArea, &ScribbleArea::undo);

    QAction *redoAction = new QAction("redo");
    redoAction->setShortcut(QKeySequence::Redo);
    ui->toolBar->addAction(redoAction);
    connect(redoAction, &QAction::triggered, m_scribbleArea, &ScribbleArea::redo);
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

void MainWindow::about()
{
    QMessageBox::StandardButton res = QMessageBox::information(this, tr("PaintApplication"),
                       tr("Application is written in C++, using QT.\n"
                          "Originally made for project in university.\n\n"
                          "Version 1.0.0"),
                       QMessageBox::Ok);
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
bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    //QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               //initialPath,
                               //tr("%1 Files (*.%2);;All Files (*)")
                               //.arg(QString::fromLatin1(fileFormat.toUpper()))
                               //.arg(QString::fromLatin1(fileFormat)));
    QString fileName = QFileDialog::getSaveFileName(this, "Save As", initialPath, "PNG (*.png);;JPEG (*.jpg *.jpeg);;BMP (*.bmp)");
    if (fileName.isEmpty())
        return false;
    return m_scribbleArea->saveImage(fileName, fileFormat.constData());
}



