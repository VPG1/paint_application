#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>
#include <QAction>
#include <QColorDialog>
#include "scribblearea.h"
#include "usersettings.h"
#include "slider.h"
#include "rectangledrawstrategy.h"
#include "ellipsedrawstrategy.h"
#include "floodfillstrategy.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void changingColor();

    void chosePen();
    void choseLine();
    void choseRectangle();
    void choseEllipse();
    void choseFloodFill();
    
    void open();
    void save();
    void about();


private:
    Ui::MainWindow *ui;

    ScribbleArea *m_scribbleArea;

    QSize m_colorPixmapSize = QSize(20, 20);
    QAction *m_changeColorAction;
    QAction *m_changePenWidthAction;
    bool Pencil;
    
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);
};
#endif // MAINWINDOW_H
