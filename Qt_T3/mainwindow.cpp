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

void MainWindow::on_botaoLeDados_clicked()
{
    char config;

    sendCommand('l');

    serial->read(&config,1);
    serial->waitForBytesWritten(1000);

    if(config == 'e')
    {
        readUser();
        showUserInForms();
    }
    else if(config == 'n')
    {
        showPopUp();
    }
    else
    {
        qDebug() << "Algo deu errado lendo usuario cadastrado";
    }
    

}

void MainWindow::on_botaoCadastra_clicked()
{
    readForms();

    sendCommand('c');

    writeUser();
}

bool MainWindow::readUser()
{
    if(serial->isOpen())
    {
        serial->read((char *)&usuario,sizeof(form));
        serial->waitForBytesWritten(500);
        return true;
    }
    else
    {
        qDebug() << "Erro ao ler o usuario, serial nao aberta";
        return false;
    }
    return false;    
}

bool MainWindow::writeUser()
{
    if(serial->isOpen())
    {
        serial->write((char *)&usuario,sizeof(form));
        serial->waitForBytesWritten(500);
        return true;
    }
    else
    {
        qDebug() << "Erro ao escrever no usuario, serial nao aberta";
        return false;
    }
    return false;  
}

void MainWindow::showUserInForms()
{
    ui->nome->setText(usuario.nome);
    ui->matricula->setText(usuario.matricula);
    ui->cargo->setText(usuario.cargo);
    ui->hora_saida->setText(usuario.hora_saida);
    ui->data_saida->setText(usuario.data_saida);
    ui->hora_entrada->setText(usuario.hora_entrada);
    ui->data_entrada->setText(usuario.data_entrada);

}

void MainWindow::showPopUp()
{

}

void MainWindow::readForms()
{
    QString text = ui->nome->text();
    strcpy(usuario.nome, text.toLatin1());

    text = ui->matricula->text();
    strcpy(usuario.matricula, text.toLatin1());

    text = ui->cargo->text();
    strcpy(usuario.cargo, text.toLatin1());

    text = ui->hora_entrada->text();
    strcpy(usuario.hora_entrada, text.toLatin1());

    text = ui->data_entrada->text();
    strcpy(usuario.data_entrada, text.toLatin1());

    text = ui->hora_saida->text();
    strcpy(usuario.hora_saida, text.toLatin1());

    text = ui->data_saida->text();
    strcpy(usuario.data_saida, text.toLatin1());
}

void MainWindow::on_botaoApagaDados_clicked()
{
    sendCommand('a');
}

void MainWindow::on_botaoAtiva_clicked()
{
    //mostra pop up de entrar ou sair
    //faz algo
}