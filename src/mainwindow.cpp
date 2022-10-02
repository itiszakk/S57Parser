#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , log(nullptr)
    , parser(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    log = new Logger(ui->logBrowser);

    /* Set required enviroment variables (if not defined already):
     * 1. GDAL_DATA
     * 2. GDAL_DRIVER_PATH */
#ifndef QT_DEBUG
    QString cwd = QCoreApplication::applicationDirPath();
    QString gdalData = QString(cwd).append("/gdal-data");
    QString gdalDriverPath = QString(cwd).append("/gdal-plugins");

    if (qEnvironmentVariableIsEmpty(GDAL_DATA_ENVIROMENT_VARIABLE))
        qputenv(GDAL_DATA_ENVIROMENT_VARIABLE, qPrintable(gdalData));

    if (qEnvironmentVariableIsEmpty(GDAL_DRIVER_PATH_ENVIROMENT_VARIABLE))
        qputenv(GDAL_DRIVER_PATH_ENVIROMENT_VARIABLE, qPrintable(gdalDriverPath));
#endif
}

MainWindow::~MainWindow()
{
    delete parser;
    delete log;
    delete ui;
}

void MainWindow::on_inputButton_clicked()
{
    inputFilePath = QFileDialog::getOpenFileName(this, "Select input file", "", INPUT_FILE_FILTER);

    ui->inputLine->setText(inputFilePath);
}


void MainWindow::on_outputButton_clicked()
{
    outputFileDirectory = QFileDialog::getExistingDirectory(this, "Select output directory");

    if (outputFileDirectory.size())
    {
        ui->outputLine->setText(outputFileDirectory + '/' + OUTPUT_FILE_NAME);
    }
}

void MainWindow::on_runButton_clicked()
{  
    if (!inputFilePath.size())
    {
        log->error("Select input file");
        return;
    }

    if (!outputFileDirectory.size())
    {
        log->error("Select output directory");
        return;
    }

    ui->logBrowser->clear();

    QString outputFilePath = QString(outputFileDirectory).append("/").append(OUTPUT_FILE_NAME);

    parser = new S57Parser(inputFilePath, outputFilePath, log);
    parser->parse();
}
