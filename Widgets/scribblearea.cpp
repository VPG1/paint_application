#include "scribblearea.h"

ScribbleArea::ScribbleArea(QWidget *parent)
    :  QWidget(parent), image(1000, 1000, QImage::Format_RGB32)
{
    image.fill(Qt::white);

    // содержимое находится в верхнем левом углу и не изменеяется при изменении размеров окна
    setAttribute(Qt::WA_StaticContents);

    previousStates.push_back(image.copy());
    curImage = previousStates.begin();

//    drawStrategy = std::unique_ptr<RectangleDrawStrategy>(new RectangleDrawStrategy);

//    connect(UserSettings::getInstance()->drawStrategy.get(), &DrawStrategy::updateArea, this, &ScribbleArea::updateAreaSlot);
}

ScribbleArea::~ScribbleArea()
{
}

void ScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect boudingRect = event->rect(); // область которую нужно перерисовать
    painter.drawImage(boudingRect, image, boudingRect);
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    // удаляем все состояния канвы следующие за текущим
    if(curImage != previousStates.end() - 1){
        previousStates.assign(previousStates.begin(), curImage + 1);
    }


    if(event->button() == Qt::LeftButton){
        UserSettings::getInstance()->drawStrategy->press(event, &image);

        scribbling = true;

        update();
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && scribbling){
        UserSettings::getInstance()->drawStrategy->move(event);

        update();
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && scribbling){
        UserSettings::getInstance()->drawStrategy->release(event);

        scribbling = false;

        update();


        previousStates.push_back(image.copy());

        ++curImage;
        if(previousStates.size() >= 51){
            previousStates.pop_front();
        }
    }
}

void ScribbleArea::updateAreaSlot(QRect rect)
{
    update(rect);
}

void ScribbleArea::undo()
{
    // если есть предыдущие состояние канвы и в данный момент не рисуем то делаем undo
    if(curImage != previousStates.begin() && !scribbling){
        --curImage;
        image = curImage->copy();
        update();
    }
}

void ScribbleArea::redo()
{
    // если есть следущие состояние канвы и в данный момент не рисуем то делаем redo
    if(curImage != previousStates.end() - 1 && !scribbling){
        ++curImage;
        image = curImage->copy();
        update();
    }
}
