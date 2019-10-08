#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <QMessageBox>

typedef struct
{
    char cadastrado;
    char config;
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
    cadastrando = false;
}

MainWindow::~MainWindow()
{
    serial->close();
    delete ui;
}

void MainWindow::on_BotaoConecta_clicked()
{
    serialConnect();

    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();

    sprintf(usuario.hora_entrada,"%02d:%02d:%02d",time.hour(),time.minute(),time.second());
    sprintf(usuario.data_entrada,"%02d:%02d:%02d",date.day(),date.month(),date.year()%100);

    usuario.config = 'h';
    writeUser();
}

void MainWindow::serialConnect()
{
    serial->setPortName("COM5");
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

void MainWindow::readData()
{

}

void MainWindow::on_botaoLeDados_clicked()
{
    usuario.config = 'l';
    writeUser();
    readUser();

    if(usuario.cadastrado == 'c')
    {
        showUserInForms();
    }
    else
    {
        showPopUp();
    }

}

void MainWindow::on_botaoCadastra_clicked()
{
    if(cadastrando == true)
    {
        readForms();
        usuario.config = 'c';
        writeUser();

        qDebug() << "Cadastrado";
        cadastrando = false;
    }
    else
    {
        qDebug() << "Cadastramento nao habilitado";
    }

}

bool MainWindow::readUser()
{
    if(serial->bytesAvailable()>=sizeof(form))
    {
        serial->read((char*)&usuario,sizeof(form));
    }
}

bool MainWindow::writeUser()
{
    serial->write((char*)&usuario,sizeof(form));
    serial->waitForBytesWritten(500);
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
    QMessageBox msgBox;

    msgBox.setText("Usuario não cadastrado, cadastrar?");
    QPushButton *sim = msgBox.addButton(tr("Sim"), QMessageBox::ActionRole);
    QPushButton *nao = msgBox.addButton(tr("Nao"), QMessageBox::ActionRole);

    msgBox.exec();

    if(msgBox.clickedButton() == sim)
    {
        qDebug() << "CADASTRANDO";
        cadastrando = 1;
    }
    else if(msgBox.clickedButton() == nao)
    {
        qDebug() << "nao no cadastrar, nada acontece";
    }

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
    usuario.config = 'a';
    writeUser();
}

void MainWindow::on_botaoAtiva_clicked()
{
    QMessageBox msgBox;
    QPushButton *entrar = msgBox.addButton(tr("Entrar"), QMessageBox::ActionRole);
    QPushButton *sair = msgBox.addButton(tr("Sair"), QMessageBox::ActionRole);

    msgBox.setWindowTitle("Entrando ou Saindo?");

    msgBox.exec();

    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();

    char str[100];
    sprintf(str,"%02d:%02d:%02d", time.hour(), time.minute(), time.second());
    strcpy(usuario.hora_entrada,str);
    strcpy(usuario.hora_saida,str);

    sprintf(str,"%02d:%02d:%02d", date.day(), date.month(), date.year()%100);
    strcpy(usuario.data_entrada,str);
    strcpy(usuario.data_saida,str);

    if(msgBox.clickedButton() == entrar)
    {
        qDebug() << "entrando";
        usuario.config = 'o';
        writeUser();

    }
    else if(msgBox.clickedButton() == sair)
    {
        qDebug() << "saindo";
        usuario.config = 'u';
        writeUser();
    }

}
