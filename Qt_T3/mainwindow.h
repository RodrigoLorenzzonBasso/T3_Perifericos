#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QThread>
#include <QDebug>
#include <QTime>
#include <QDate>

#include <string.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_BotaoConecta_clicked();
    void readData();

    void on_botaoEnvia_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;

    void serialConnect();
    void transmitSystemHour();
    void sendCommand(char com);
};

#endif // MAINWINDOW_H
