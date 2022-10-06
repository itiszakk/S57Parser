#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QAnyStringView>
#include <QSettings>
#include <QVariant>
#include <QPointF>
#include <QTableWidgetItem>

#include "logger.h"
#include "s57_parser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_inputButton_clicked();
    void on_outputButton_clicked();
    void on_runButton_clicked();
    void on_configTable_itemChanged(QTableWidgetItem *item);

private:
    QMap<QString, QVariant> settings;

    Logger *log;
    S57Parser *parser;
    Ui::MainWindow *ui;

    QString inputFilePath;
    QString outputFileDirectory;

    void initSettings();
    bool checkSettingsValue(QString key, QString valueAsString, QVariant *valuePtr);
    void doActionsWhenChangedSetting(QString key);
    void setInputLine();
    void setOutputLine();
    void fillConfigurationTable();
};
#endif // MAINWINDOW_H
