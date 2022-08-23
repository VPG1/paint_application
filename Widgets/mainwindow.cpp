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
    connect(ui->toolBar->addAction("open"),
            &QAction::triggered, this, &MainWindow::open);
    connect(ui->toolBar->addAction("save"),
            &QAction::triggered, this, &MainWindow::save);




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
            scribbleArea->openImage(fileName);
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
    if (scribbleArea->isModified()) {
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

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty())
        return false;
    return scribbleArea->saveImage(fileName, fileFormat.constData());
}



