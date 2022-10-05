#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , log(nullptr)
    , parser(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentWidget(ui->configTab);

    log = new Logger(ui->logBrowser);

    initSettings();

    setEnviroment();

    fillConfigurationTable();
}

MainWindow::~MainWindow()
{
    delete parser;
    delete log;
    delete ui;
}

void MainWindow::on_inputButton_clicked()
{
    inputFilePath = QFileDialog::getOpenFileName(this, "Select input file");
    setInputLine();
}


void MainWindow::on_outputButton_clicked()
{
    outputFileDirectory = QFileDialog::getExistingDirectory(this, "Select output directory");
    setOutputLine();
}

void MainWindow::on_configTable_itemChanged(QTableWidgetItem *item)
{
    /* configTable value changed */
    if (item->column() == 1) {
        QString key = item->tableWidget()->item(item->row(), 0)->text();
        QVariant value;

        qDebug() << settings[key];

        bool correctValue = checkSettingsValue(key, item->text(), &value);

        if (!correctValue) {
            ui->configTable->blockSignals(true);
            ui->tabWidget->setCurrentWidget(ui->logTab);
            item->setText(settings[key].toString());
            ui->configTable->blockSignals(false);
            return;
        }

        settings[key] = value;

        qDebug() << settings[key];

        if (key == "output.file.name") {
            setOutputLine();
        }
    }
}

void MainWindow::on_runButton_clicked()
{  
    ui->logBrowser->clear();
    ui->tabWidget->setCurrentWidget(ui->logTab);

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

    QString outputFilePath = QString(outputFileDirectory).append("/").append(settings["output.file.name"].toString());

    parser = new S57Parser(inputFilePath, outputFilePath, settings, log);
    parser->parse();
}

void MainWindow::initSettings()
{
    settings["output.file.name"] = "map.json";

    settings["coordinate.scale.x"] = 400.0;
    settings["coordinate.scale.y"] = 400.0;

    settings["grid.border.left"] = 0;
    settings["grid.border.bottom"] = 0;
    settings["grid.border.right"] = 40000;
    settings["grid.border.top"] = 40000;

    settings["grid.ticks.x"] = 400;
    settings["grid.ticks.y"] = 400;
}

bool MainWindow::checkSettingsValue(QString key, QString valueAsString, QVariant *valuePtr = nullptr)
{
    QMetaType::Type valueType = static_cast<QMetaType::Type>(settings[key].typeId());

    if (!valueAsString.size())
    {

        log->error(QString("Setting '%1' value is missing").arg(key));
        return false;
    }

    bool canConvert = false;

    switch(valueType)
    {

    case QMetaType::Type::Int:
    {
        *valuePtr = QVariant(valueAsString.toInt(&canConvert));
    } break;

    case QMetaType::Type::Double:
    {
        *valuePtr = QVariant(valueAsString.toDouble(&canConvert));
    } break;

    case QMetaType::Type::QString:
    {
        *valuePtr = QVariant(valueAsString);
        canConvert = true;
    } break;

    /* Implement for other types */
    default: break;
    }

    if (!canConvert) {
        log->error(QString("Failed to convert '%1' to type '%2'").arg(key, QMetaType(valueType).name()));
        return false;
    }

    return true;
}

void MainWindow::setInputLine()
{
    ui->inputLine->setText(inputFilePath);
}

void MainWindow::setOutputLine()
{
    if (outputFileDirectory.size())
    {
        ui->outputLine->setText(outputFileDirectory + '/' + settings["output.file.name"].toString());
    }
}

void MainWindow::fillConfigurationTable()
{
    ui->configTable->blockSignals(true);

    QList<QString> settingsKeyList = settings.keys();

    for (const QString &key : settingsKeyList)
    {
        int currentRow = ui->configTable->rowCount();

        ui->configTable->setRowCount(currentRow + 1);

        QTableWidgetItem *keyItem = new QTableWidgetItem();
        QTableWidgetItem *valueItem = new QTableWidgetItem();

        keyItem->setText(key);
        keyItem->setFlags(Qt::ItemIsEnabled);

        valueItem->setText(settings[key].toString());
        valueItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);


        ui->configTable->setItem(currentRow, 0, keyItem);
        ui->configTable->setItem(currentRow, 1, valueItem);
    }

    ui->configTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->configTable->blockSignals(false);
}

/* Set required GDAL environment variables for release version (if not defined already): */
void MainWindow::setEnviroment()
{
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

