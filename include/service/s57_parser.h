#ifndef S57_PARSER_H
#define S57_PARSER_H

#include "logger.h"
#include "gdal_manager.h"
#include "model.h"

#include <QDebug>
#include <QSettings>
#include <QString>
#include <QVector2D>
#include <QVector3D>
#include <QJsonDocument>
#include <QJsonArray>
#include <QByteArray>
#include <QFile>
#include <algorithm>

class S57Parser
{
public:
    S57Parser(const QString &inputFilePath, const QString &outputFilePath, QMap<QString, QVariant> settings, Logger *log);
    ~S57Parser();

    void parse();

private:
    const QString WATER_LAYER_ACRONYM = "DEPARE";
    const QString SURFACE_LAYER_ACRONYM = "LNDARE";
    const QString SOUNDING_LAYER_ACRONYM = "SOUNDG";
    const QString COVERAGE_LAYER_ACRONYM = "M_COVR";
    const QString WATER_MIN_DEPTH = "DRVAL1";
    const QString WATER_MAX_DEPTH = "DRVAL2";
    const QString GEOMETRY_POLYGON = "POLYGON";
    const QString GEOMETRY_POINT = "POINT";
    const double MIN_LATITUDE = -90.0;
    const double MAX_LATITUDE = 90.0;
    const double MIN_LONGITUDE = -180.0;
    const double MAX_LONGITUDE = 180.0;
    const int SURFACE_LEVEL = 0.0;

    QMap<QString, QVariant> settings;

    Logger *log;
    GDALManager *gdal;

    Model::Map *map;

    QString inputFilePath;
    QString outputFilePath;
    QVector2D coordinateOffset;
    QVector2D maxCoordinate;

    Model::Grid* getGridBySettings();

    void setCoordinateOffset(OGRLayer* coverageLayer);
    void waterLayerHandler(OGRLayer* waterLayer);
    void surfaceLayerHandler(OGRLayer* surfaceLayer);
    void soundingLayerHandler(OGRLayer* soundingLayer);

    Model::Point getAdjustedPoint(QVector2D point);

    bool saveOutputJson(bool compact = false);
};

#endif // S57_PARSER_H
