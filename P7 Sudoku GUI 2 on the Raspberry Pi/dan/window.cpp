#include "window.h"

#include <QPainter>
#include <QDebug>

Window::Window(QWidget *parent) : QWidget(parent)
{
   setFixedSize(400,600);
}

void Window::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    QPen pen;
    QFont font;
    font.setPixelSize(30);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.setFont(font);
    QPoint p1(10,20), p2(80,60);
    painter.drawLine(p1, p2);
    painter.drawText(120,200,tr("1"));
}

void Window::mouseReleaseEvent(QMouseEvent * event) 
{
    qDebug() << "Mouse x " << event->x() << " Mouse y " << event->y();
}
