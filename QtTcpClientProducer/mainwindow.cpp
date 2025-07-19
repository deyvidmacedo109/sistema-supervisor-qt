
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

// No construtor MainWindow::MainWindow(...)
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    // Inicializar o timer
    timer = new QTimer(this);

    // Conectar o timeout do timer ao slot putData
    connect(timer, SIGNAL(timeout()), this, SLOT(putData()));

    // Conectar os botões da UI aos novos slots
    // (Assumindo que você tenha botões 'pushButtonStart' e 'pushButtonStop' na sua UI)
    connect(ui->pushButtonStart, SIGNAL(clicked(bool)), this, SLOT(startSending()));
    connect(ui->pushButtonStop, SIGNAL(clicked(bool)), this, SLOT(stopSending()));

    // Conexões antigas
    connect(ui->pushButtonConnect, SIGNAL(clicked(bool)), this, SLOT(tcpConnect()));
    connect(ui->pushButtonDisconnect, SIGNAL(clicked(bool)), this, SLOT(tcpDisconnect()));
}

// Nova função para iniciar o envio
void MainWindow::startSending(){
    // Lê o intervalo do QSpinBox 'timingSpinBox' (exemplo)
    // Multiplica por 1000 para converter segundos em milissegundos
    int interval = ui->timingSpinBox->value() * 1000;
    if (interval > 0) {
        timer->start(interval);
    }
}

// Nova função para parar o envio
void MainWindow::stopSending(){
    timer->stop();
}


// Função putData modificada
void MainWindow::putData(){
    QDateTime datetime;
    QString str;
    qint64 msecdate;

    if(socket->state() == QAbstractSocket::ConnectedState){
        // Lê os valores min/max da UI (ex: de QSpinBox)
        int min = ui->minSpinBox->value();
        int max = ui->maxSpinBox->value();

        // Garante que max seja maior ou igual a min
        if (max < min) {
            return;
        }

        // Gera um valor aleatório na faixa definida
        int randomValue = min + rand() % (max - min + 1);

        msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
        str = "set " + QString::number(msecdate) + " " + QString::number(randomValue) + "\r\n";

        // Exibe o dado enviado na UI (ex: em um QTextEdit 'dataTextEdit')
        ui->dataTextEdit->appendPlainText(str.trimmed());

        qDebug() << str;
        socket->write(str.toStdString().c_str());
        socket->waitForBytesWritten(1000);
    }
}

void MainWindow::tcpConnect(){
  socket->connectToHost(ui->ipLineEdit->text(),1234);
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

MainWindow::~MainWindow(){
  delete socket;
  delete ui;
}
