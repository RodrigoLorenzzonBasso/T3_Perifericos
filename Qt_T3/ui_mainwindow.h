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
    QLineEdit *envia;
    QPushButton *botaoEnvia;
    QLineEdit *recebe;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *recebe_2;
    QLineEdit *recebe_3;
    QLineEdit *recebe_4;
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
        envia = new QLineEdit(centralWidget);
        envia->setObjectName(QStringLiteral("envia"));
        envia->setGeometry(QRect(70, 60, 211, 21));
        botaoEnvia = new QPushButton(centralWidget);
        botaoEnvia->setObjectName(QStringLiteral("botaoEnvia"));
        botaoEnvia->setGeometry(QRect(120, 250, 75, 23));
        recebe = new QLineEdit(centralWidget);
        recebe->setObjectName(QStringLiteral("recebe"));
        recebe->setGeometry(QRect(70, 90, 211, 20));
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
        recebe_2 = new QLineEdit(centralWidget);
        recebe_2->setObjectName(QStringLiteral("recebe_2"));
        recebe_2->setGeometry(QRect(100, 120, 151, 20));
        recebe_3 = new QLineEdit(centralWidget);
        recebe_3->setObjectName(QStringLiteral("recebe_3"));
        recebe_3->setGeometry(QRect(130, 170, 211, 20));
        recebe_4 = new QLineEdit(centralWidget);
        recebe_4->setObjectName(QStringLiteral("recebe_4"));
        recebe_4->setGeometry(QRect(130, 200, 211, 20));
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
        botaoEnvia->setText(QApplication::translate("MainWindow", "Envia", nullptr));
        label->setText(QApplication::translate("MainWindow", "Ponto Eletronico", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Nome", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Cargo", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Matr\303\255cula", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Ultima Entrada", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Ultima Sa\303\255da", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
