/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *inputLabel;
    QLabel *outputLabel;
    QPushButton *inputButton;
    QPushButton *outputButton;
    QPushButton *runButton;
    QLineEdit *inputLine;
    QLineEdit *outputLine;
    QTextBrowser *logBrowser;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(630, 265);
        MainWindow->setMinimumSize(QSize(630, 265));
        MainWindow->setMaximumSize(QSize(630, 265));
        QFont font;
        font.setFamilies({QString::fromUtf8("Calibri")});
        font.setPointSize(10);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        inputLabel = new QLabel(centralwidget);
        inputLabel->setObjectName("inputLabel");
        inputLabel->setGeometry(QRect(10, 10, 71, 16));
        inputLabel->setFont(font);
        outputLabel = new QLabel(centralwidget);
        outputLabel->setObjectName("outputLabel");
        outputLabel->setGeometry(QRect(10, 40, 71, 16));
        outputLabel->setFont(font);
        inputButton = new QPushButton(centralwidget);
        inputButton->setObjectName("inputButton");
        inputButton->setGeometry(QRect(510, 10, 41, 21));
        inputButton->setFont(font);
        outputButton = new QPushButton(centralwidget);
        outputButton->setObjectName("outputButton");
        outputButton->setGeometry(QRect(510, 40, 41, 21));
        outputButton->setFont(font);
        runButton = new QPushButton(centralwidget);
        runButton->setObjectName("runButton");
        runButton->setGeometry(QRect(560, 10, 61, 51));
        runButton->setFont(font);
        inputLine = new QLineEdit(centralwidget);
        inputLine->setObjectName("inputLine");
        inputLine->setGeometry(QRect(80, 10, 421, 21));
        inputLine->setFont(font);
        inputLine->setReadOnly(true);
        outputLine = new QLineEdit(centralwidget);
        outputLine->setObjectName("outputLine");
        outputLine->setGeometry(QRect(80, 40, 421, 21));
        outputLine->setFont(font);
        outputLine->setReadOnly(true);
        logBrowser = new QTextBrowser(centralwidget);
        logBrowser->setObjectName("logBrowser");
        logBrowser->setGeometry(QRect(10, 70, 611, 171));
        logBrowser->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "S57Parser", nullptr));
        inputLabel->setText(QCoreApplication::translate("MainWindow", "Input file:", nullptr));
        outputLabel->setText(QCoreApplication::translate("MainWindow", "Output file:", nullptr));
        inputButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        outputButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        runButton->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
