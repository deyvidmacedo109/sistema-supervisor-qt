#include "plotter.h"
#include <QPainter> //algoritimos para desenhar
#include <QBrush>
#include <QPen>

Plotter::Plotter(QWidget *parent)
    : QWidget{parent}
{}

void Plotter::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    QBrush brush;
    QPen pen;

    brush.setColor(QColor(195,233,238));
    brush.setStyle(Qt::SolidPattern);

    pen.setColor(QColor(90,80,153));
    pen.setWidth(4);

    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(4,4,width()-8,height()-8);

}
