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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *mainWidget;
    QLabel *inputLabel;
    QLabel *outputLabel;
    QPushButton *inputButton;
    QPushButton *outputButton;
    QLineEdit *inputLine;
    QLineEdit *outputLine;
    QTabWidget *tabWidget;
    QWidget *configTab;
    QGridLayout *gridLayout;
    QTableWidget *configTable;
    QWidget *logTab;
    QGridLayout *gridLayout_2;
    QTextBrowser *logBrowser;
    QPushButton *runButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(630, 330);
        MainWindow->setMinimumSize(QSize(630, 330));
        MainWindow->setMaximumSize(QSize(630, 330));
        QFont font;
        font.setFamilies({QString::fromUtf8("Calibri")});
        font.setPointSize(10);
        MainWindow->setFont(font);
        mainWidget = new QWidget(MainWindow);
        mainWidget->setObjectName("mainWidget");
        inputLabel = new QLabel(mainWidget);
        inputLabel->setObjectName("inputLabel");
        inputLabel->setGeometry(QRect(9, 9, 52, 16));
        inputLabel->setFont(font);
        outputLabel = new QLabel(mainWidget);
        outputLabel->setObjectName("outputLabel");
        outputLabel->setGeometry(QRect(9, 38, 61, 16));
        outputLabel->setFont(font);
        inputButton = new QPushButton(mainWidget);
        inputButton->setObjectName("inputButton");
        inputButton->setGeometry(QRect(465, 9, 75, 23));
        inputButton->setFont(font);
        outputButton = new QPushButton(mainWidget);
        outputButton->setObjectName("outputButton");
        outputButton->setGeometry(QRect(465, 38, 75, 23));
        outputButton->setFont(font);
        inputLine = new QLineEdit(mainWidget);
        inputLine->setObjectName("inputLine");
        inputLine->setGeometry(QRect(76, 10, 381, 21));
        inputLine->setFont(font);
        inputLine->setReadOnly(true);
        outputLine = new QLineEdit(mainWidget);
        outputLine->setObjectName("outputLine");
        outputLine->setGeometry(QRect(76, 39, 381, 21));
        outputLine->setFont(font);
        outputLine->setReadOnly(true);
        tabWidget = new QTabWidget(mainWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(9, 70, 611, 239));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setDocumentMode(false);
        configTab = new QWidget();
        configTab->setObjectName("configTab");
        gridLayout = new QGridLayout(configTab);
        gridLayout->setObjectName("gridLayout");
        configTable = new QTableWidget(configTab);
        if (configTable->columnCount() < 2)
            configTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        configTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        configTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        configTable->setObjectName("configTable");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(configTable->sizePolicy().hasHeightForWidth());
        configTable->setSizePolicy(sizePolicy);
        configTable->setFocusPolicy(Qt::NoFocus);
        configTable->setLayoutDirection(Qt::LeftToRight);
        configTable->setAutoFillBackground(false);
        configTable->setFrameShape(QFrame::StyledPanel);
        configTable->setFrameShadow(QFrame::Plain);
        configTable->setLineWidth(1);
        configTable->setMidLineWidth(0);
        configTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        configTable->setAlternatingRowColors(false);
        configTable->setSelectionMode(QAbstractItemView::NoSelection);
        configTable->setShowGrid(true);
        configTable->setGridStyle(Qt::SolidLine);
        configTable->setSortingEnabled(true);
        configTable->setCornerButtonEnabled(true);
        configTable->setRowCount(0);
        configTable->horizontalHeader()->setVisible(true);
        configTable->horizontalHeader()->setCascadingSectionResizes(false);
        configTable->horizontalHeader()->setHighlightSections(true);
        configTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        configTable->horizontalHeader()->setStretchLastSection(true);
        configTable->verticalHeader()->setVisible(false);
        configTable->verticalHeader()->setHighlightSections(false);
        configTable->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        configTable->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(configTable, 0, 0, 1, 1);

        tabWidget->addTab(configTab, QString());
        logTab = new QWidget();
        logTab->setObjectName("logTab");
        gridLayout_2 = new QGridLayout(logTab);
        gridLayout_2->setObjectName("gridLayout_2");
        logBrowser = new QTextBrowser(logTab);
        logBrowser->setObjectName("logBrowser");
        logBrowser->setFont(font);

        gridLayout_2->addWidget(logBrowser, 0, 0, 1, 1);

        tabWidget->addTab(logTab, QString());
        runButton = new QPushButton(mainWidget);
        runButton->setObjectName("runButton");
        runButton->setGeometry(QRect(546, 9, 75, 51));
        runButton->setFont(font);
        MainWindow->setCentralWidget(mainWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "S57Parser", nullptr));
        inputLabel->setText(QCoreApplication::translate("MainWindow", "Input file:", nullptr));
        outputLabel->setText(QCoreApplication::translate("MainWindow", "Output file:", nullptr));
        inputButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        outputButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        QTableWidgetItem *___qtablewidgetitem = configTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Key", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = configTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Value", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(configTab), QCoreApplication::translate("MainWindow", "Configuration", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(logTab), QCoreApplication::translate("MainWindow", "Log", nullptr));
        runButton->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
