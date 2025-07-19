// QtTcpClientConsumer/mainwindow.cpp

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

// No construtor MainWindow::MainWindow(...)
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    timer = new QTimer(this);

    // Conecta o sinal readyRead() ao nosso novo slot
    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));

    // Conecta o timer ao slot que pede os dados
    connect(timer, SIGNAL(timeout()), this, SLOT(getData()));

    // Conecta os botões da UI aos slots
    // (Assumindo botões 'pushButtonUpdate', 'pushButtonStart', 'pushButtonStop')
    connect(ui->pushButtonUpdate,
            SIGNAL(clicked(bool)),
            this,
            SLOT(updateIpList()));
    connect(ui->pushButtonStart,
            SIGNAL(clicked(bool)),
            this,
            SLOT(startFetching()));
    connect(ui->pushButtonStop,
            SIGNAL(clicked(bool)),
            this,
            SLOT(stopFetching()));
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

// Slot para pedir a lista de IPs
void MainWindow::updateIpList(){
    if(socket->state() == QAbstractSocket::ConnectedState){
        socket->write("list\r\n");
    }
}

// Slot para iniciar a busca de dados
void MainWindow::startFetching(){
    int interval = ui->timingSpinBox->value() * 1000;
    if(interval > 0){
        timer->start(interval);
    }
}

// Slot para parar a busca
void MainWindow::stopFetching(){
    timer->stop();
}

// Slot que é chamado pelo timer para pedir os dados
void MainWindow::getData(){
    // Limpa os pontos antigos antes de pedir novos
    dataPoints.clear();

    if(socket->state() == QAbstractSocket::ConnectedState){
        // Pega o IP selecionado no QListWidget (ex: 'ipListWidget')
        QListWidgetItem *selectedItem = ui->ipListWidget->currentItem();
        if (!selectedItem) {
            return; // Não faz nada se nenhum IP estiver selecionado
        }
        QString ip = selectedItem->text();

        // Pede as últimas 30 amostras (exemplo)
        QString command = "get " + ip + " 30\r\n";
        socket->write(command.toUtf8());
    }
}

// Slot para processar os dados recebidos do socket
void MainWindow::readData(){
    while(socket->canReadLine()){
        QString line = socket->readLine().trimmed();

        qDebug() << "DADO BRUTO DO SERVIDOR:" << line;

        line.replace("\"", "");

        if(line.isEmpty() || line.toLower() == "list"){
            continue;
        }

        QStringList parts = line.split(" ");

        if (parts.size() == 1) {
            QString ip = parts.at(0);
            if(ui->ipListWidget->findItems(ip, Qt::MatchExactly).isEmpty()){
                ui->ipListWidget->addItem(ip);
            }
        }
        else if (parts.size() == 2) {
            bool ok;
            qint64 time = parts.at(0).toLongLong(&ok);
            if (ok) {
                double value = parts.at(1).toDouble();
                dataPoints.append(QPointF(time, value));
            }
        }
    }
    ui->centralWidget_2->setData(dataPoints);
}

void MainWindow::tcpConnect(){
    socket->connectToHost(ui->ipLineEdit->text(), 1234);
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

MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}
