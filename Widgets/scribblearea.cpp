#include "scribblearea.h"

ScribbleArea::ScribbleArea(QWidget *parent)
    :  QWidget(parent), m_image(1000, 1000, QImage::Format_RGB32)
{
    m_image.fill(Qt::white);

    // содержимое находится в верхнем левом углу и не изменеяется при изменении размеров окна
    setAttribute(Qt::WA_StaticContents);

    m_previousStates.push_back(m_image.copy());
    m_curImage = m_previousStates.begin();

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
    painter.drawImage(boudingRect, m_image, boudingRect);
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    // удаляем все состояния канвы следующие за текущим
    if(m_curImage != m_previousStates.end() - 1){
        m_previousStates.assign(m_previousStates.begin(), m_curImage + 1);
    }


    if(event->button() == Qt::LeftButton){
        UserSettings::getInstance()->drawStrategy->press(event, &m_image);

        m_scribbling = true;

        update();
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && m_scribbling){
        UserSettings::getInstance()->drawStrategy->move(event);

        update();
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_scribbling){
        UserSettings::getInstance()->drawStrategy->release(event);

        m_scribbling = false;

        update();


        m_previousStates.push_back(m_image.copy());

        ++m_curImage;
        if(m_previousStates.size() >= 51){
            m_previousStates.pop_front();
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
    if(m_curImage != m_previousStates.begin() && !m_scribbling){
        --m_curImage;
        m_image = m_curImage->copy();
        update();
    }
}

void ScribbleArea::redo()
{
    // если есть следущие состояние канвы и в данный момент не рисуем то делаем redo
    if(m_curImage != m_previousStates.end() - 1 && !m_scribbling){
        ++m_curImage;
        m_image = m_curImage->copy();
        update();
    }
}
