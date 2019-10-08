/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *BotaoConecta;
    QLineEdit *nome;
    QLineEdit *cargo;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *matricula;
    QLineEdit *hora_entrada;
    QLineEdit *hora_saida;
    QLineEdit *data_entrada;
    QLineEdit *data_saida;
    QPushButton *botaoLeDados;
    QPushButton *botaoApagaDados;
    QPushButton *botaoAtiva;
    QPushButton *botaoCadastra;
    QLabel *label_7;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(512, 349);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BotaoConecta = new QPushButton(centralWidget);
        BotaoConecta->setObjectName(QStringLiteral("BotaoConecta"));
        BotaoConecta->setGeometry(QRect(30, 250, 75, 23));
        nome = new QLineEdit(centralWidget);
        nome->setObjectName(QStringLiteral("nome"));
        nome->setGeometry(QRect(70, 60, 211, 21));
        cargo = new QLineEdit(centralWidget);
        cargo->setObjectName(QStringLiteral("cargo"));
        cargo->setGeometry(QRect(70, 90, 151, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(160, 0, 181, 41));
        QFont font;
        font.setFamily(QStringLiteral("Comic Sans MS"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 50, 61, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Comic Sans MS"));
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        label_2->setFont(font1);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 80, 61, 31));
        label_3->setFont(font1);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 110, 91, 31));
        label_4->setFont(font1);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 160, 111, 31));
        QFont font2;
        font2.setFamily(QStringLiteral("Comic Sans MS"));
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(75);
        label_5->setFont(font2);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 190, 111, 31));
        label_6->setFont(font2);
        matricula = new QLineEdit(centralWidget);
        matricula->setObjectName(QStringLiteral("matricula"));
        matricula->setGeometry(QRect(100, 120, 101, 20));
        hora_entrada = new QLineEdit(centralWidget);
        hora_entrada->setObjectName(QStringLiteral("hora_entrada"));
        hora_entrada->setGeometry(QRect(130, 170, 71, 20));
        hora_saida = new QLineEdit(centralWidget);
        hora_saida->setObjectName(QStringLiteral("hora_saida"));
        hora_saida->setGeometry(QRect(130, 200, 71, 20));
        data_entrada = new QLineEdit(centralWidget);
        data_entrada->setObjectName(QStringLiteral("data_entrada"));
        data_entrada->setGeometry(QRect(210, 170, 71, 20));
        data_saida = new QLineEdit(centralWidget);
        data_saida->setObjectName(QStringLiteral("data_saida"));
        data_saida->setGeometry(QRect(210, 200, 71, 20));
        botaoLeDados = new QPushButton(centralWidget);
        botaoLeDados->setObjectName(QStringLiteral("botaoLeDados"));
        botaoLeDados->setGeometry(QRect(120, 250, 75, 23));
        botaoApagaDados = new QPushButton(centralWidget);
        botaoApagaDados->setObjectName(QStringLiteral("botaoApagaDados"));
        botaoApagaDados->setGeometry(QRect(210, 250, 75, 23));
        botaoAtiva = new QPushButton(centralWidget);
        botaoAtiva->setObjectName(QStringLiteral("botaoAtiva"));
        botaoAtiva->setGeometry(QRect(300, 250, 75, 23));
        botaoCadastra = new QPushButton(centralWidget);
        botaoCadastra->setObjectName(QStringLiteral("botaoCadastra"));
        botaoCadastra->setGeometry(QRect(390, 250, 75, 23));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(410, 40, 51, 41));
        QFont font3;
        font3.setFamily(QStringLiteral("Comic Sans MS"));
        font3.setPointSize(14);
        label_7->setFont(font3);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 512, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        BotaoConecta->setText(QApplication::translate("MainWindow", "Conecta", nullptr));
        label->setText(QApplication::translate("MainWindow", "Ponto Eletronico", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Nome", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Cargo", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Matr\303\255cula", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Ultima Entrada", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Ultima Sa\303\255da", nullptr));
        botaoLeDados->setText(QApplication::translate("MainWindow", "Le Dados", nullptr));
        botaoApagaDados->setText(QApplication::translate("MainWindow", "Apaga Dados", nullptr));
        botaoAtiva->setText(QApplication::translate("MainWindow", "Envia/Ativa", nullptr));
        botaoCadastra->setText(QApplication::translate("MainWindow", "Cadastra", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Foto", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
