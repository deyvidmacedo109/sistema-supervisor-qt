#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QVector>
#include <QPointF>

class Plotter : public QWidget
{
    Q_OBJECT
public:
    explicit Plotter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void setData(const QVector<QPointF> &data);

signals:

private:
    QVector<QPointF> points;
};

#endif // PLOTTER_H
