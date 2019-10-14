#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QDebug>
#include <QTime>
#include <QDate>

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
    void readData();
    void timer_teste();

    void on_BotaoConecta_clicked();
    void on_botaoLeDados_clicked();
    void on_botaoApagaDados_clicked();
    void on_botaoCadastra_clicked();
    void on_botaoAtiva_clicked();


private:
    Ui::MainWindow *ui;
    QSerialPort *serial;

    void serialConnect();
    bool writeUser();
    void showUserInForms();
    void showPopUp();
    void readForms();
    void eraseForms();
};

#endif // MAINWINDOW_H
