// QtTcpClientConsumer/mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>
#include <QVector>
#include <QPointF>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void tcpConnect();
    void tcpDisconnect();
    void getData();
    void updateIpList();
    void startFetching();
    void stopFetching();
    void readData();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QTimer *timer;
    QVector<QPointF> dataPoints;
};

#endif // MAINWINDOW_H
