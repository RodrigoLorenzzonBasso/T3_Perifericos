#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>

typedef struct
{
    char nome[30];
    char cargo[30];
    char matricula[10];
    char hora_entrada[17];
    char data_entrada[17];
    char hora_saida[17];
    char data_saida[17];
} form;

form usuario;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
}

MainWindow::~MainWindow()
{
    serial->close();
    delete ui;
}

void MainWindow::on_BotaoConecta_clicked()
{
    serialConnect();
    sendCommand('h');
    transmitSystemHour();
}

void MainWindow::readData()
{

}

void MainWindow::serialConnect()
{
    serial->setPortName("COM4");
    serial->setBaudRate(115200);
    serial->setDataBits(static_cast<QSerialPort::DataBits>(8));
    serial->setParity(static_cast<QSerialPort::Parity>(0));
    serial->setStopBits(static_cast<QSerialPort::StopBits>(1));
    serial->setFlowControl(static_cast<QSerialPort::FlowControl>(0));

    if(serial->open(QIODevice::ReadWrite))
    {
        qDebug("Porta Serial: " + serial->portName().toLatin1() + " Aberta");
    }
    else
    {
        qDebug("Nao foi possivel abrir a porta serial");
    }
}

void MainWindow::transmitSystemHour()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();

    char str[100];
    sprintf(str,"%02d:%02d:%02d %02d/%02d/%02d", time.hour(), time.minute(), time.second(),
                                                 date.day(), date.month(), date.year()%100);

    qDebug() << str;

    if(serial->isOpen())
    {
        serial->write(str,strlen(str));
        serial->waitForBytesWritten(500);
    }
}

void MainWindow::sendCommand(char com)
{
    if(serial->isOpen())
    {
        serial->write(&com,1);
        serial->waitForBytesWritten(500);
    }
}


void MainWindow::on_botaoEnvia_clicked()
{
    QString text = ui->envia->text();

    strcpy(usuario.nome, text.toLatin1());

    if(serial->isOpen())
    {
        sendCommand('f');

        serial->write((char *)&usuario,sizeof(form));
        serial->waitForBytesWritten(500);

        serial->read((char *)&usuario,sizeof(form));
        serial->waitForBytesWritten(500);
    }

    ui->recebe->setText(usuario.nome);

}
