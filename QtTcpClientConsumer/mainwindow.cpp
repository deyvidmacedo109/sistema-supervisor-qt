#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  tcpConnect();

  connect(ui->pushButtonGet,
          SIGNAL(clicked(bool)),
          this,
          SLOT(getData()));
  connect(ui->pushButtonConnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpConnect()));
  connect(ui->pushButtonDisconnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpDisconnect()));
}

void MainWindow::tcpConnect(){
  socket->connectToHost(ui->textEdit->toPlainText(),1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}

void MainWindow::tcpDisconnect(){
    socket->disconnectFromHost();
    if(socket->state() == QAbstractSocket::UnconnectedState ||
        socket->waitForDisconnected(3000)){
        qDebug() << "Disconnected";
    }
    else{
        qDebug() << "NOT Disconnected";
    }
}

void MainWindow::getData(){
  QString str;
  QByteArray array;
  QStringList list;
  qint64 thetime;
  qDebug() << "to get data...";
  if(socket->state() == QAbstractSocket::ConnectedState){
    if(socket->isOpen()){
      qDebug() << "reading...";
      socket->write("get 127.0.0.1 5\r\n");
      socket->waitForBytesWritten();
      socket->waitForReadyRead();
      qDebug() << socket->bytesAvailable();
      while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        list = str.split(" ");
        if(list.size() == 2){
          bool ok;
          str = list.at(0);
          thetime = str.toLongLong(&ok);
          str = list.at(1);
          qDebug() << thetime << ": " << str;
        }
      }
    }
  }
}

//void MainWindow::CopiaIP(){

//    ui->listWidgetListaIP->addItem(ui->textEdit->toPlainText());
//}

//void MainWindow::DeleteIP(){
//
//    ui->listWidgetListaIP->removeItemWidget(ui->listWidgetListaIP->currentItem());
//}


MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}
