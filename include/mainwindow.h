#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>

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

private:
    const char *GDAL_DATA_ENVIROMENT_VARIABLE = "GDAL_DATA";
    const char *GDAL_DRIVER_PATH_ENVIROMENT_VARIABLE = "GDAL_DRIVER_PATH";
    const char *INPUT_FILE_FILTER = "*.000";
    const char *OUTPUT_FILE_NAME = "map.json";

    QString inputFilePath;
    QString outputFileDirectory;

    Logger *log;
    S57Parser *parser;

    Ui::MainWindow *ui;

    void setEnviroment();
};
#endif // MAINWINDOW_H
