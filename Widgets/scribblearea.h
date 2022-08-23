#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <deque>
#include "usersettings.h"
#include "pendrawstrategy.h"
#include "linedrawstrategy.h"
#include "rectangledrawstrategy.h"

class ScribbleArea : public QWidget
{
    Q_OBJECT
public:
    ScribbleArea(QWidget *parent = nullptr);
    ~ScribbleArea();
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    bool isModified() const { return modified; }
protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

private:
    QImage m_image; // переменная для хранения рисунка пользователя

    std::deque<QImage> m_previousStates;
    std::deque<QImage>::iterator m_curImage;
    
    void resizeImage(QImage *image, const QSize &newSize);
    bool scribbling = false; // происходит ли рисование в данный момент времен
    bool modified = false;

public slots:
    void updateAreaSlot(QRect rect);

    void undo();
    void redo();
};

#endif // SCRIBBLEAREA_H
