#include "gdal_manager.h"

GDALManager::GDALManager(Logger *log)
    : log(log)
    , data(nullptr)
{
    log->info("Register all GDAL drivers");

    GDALAllRegister();
}

bool GDALManager::open(const QString &filePath)
{
    log->info(QString("Opening input file '%1'").arg(filePath));

    data = GDALDataset::Open(qPrintable(filePath));

    if (data == nullptr)
    {
        log->error(QString("Failed to open input file '%1'").arg(filePath));
        return false;
    }

    return true;
}

void GDALManager::close()
{
    log->info("Closing dataset");

    GDALClose(data);
}

OGRLayer* GDALManager::getLayerByName(const QString &layerName)
{
    log->info(QString("Getting layer '%1'").arg(layerName));

    OGRLayer* layer = data->GetLayerByName(qPrintable(layerName));

    if (layer == nullptr)
    {
        log->warning(QString("Layer '%1' doesn't exists").arg(layerName));
    }

    return layer;
}

QList<OGRFeature*> GDALManager::getFeatureList(OGRLayer *layer)
{
    QList<OGRFeature*> featureList;
    OGRFeature *feature;

    while ((feature = layer->GetNextFeature()) != nullptr)
    {
        featureList.append(feature);
    }

    return featureList;
}

QString GDALManager::getFieldByName(OGRFeature *feature, const QString &fieldName)
{
    return feature->GetFieldAsString(qPrintable(fieldName));
}

QString GDALManager::getGeometryType(OGRFeature *feature)
{
    return feature->GetGeometryRef()->getGeometryName();
}

QVector2D GDALManager::getPointGeometry(OGRFeature *feature)
{
    QVector2D point;
    QJsonObject jsonGeometry = QJsonDocument::fromJson(feature->GetGeometryRef()->exportToJson()).object();

    if (jsonGeometry[JSON_GEOMETRY_TYPE_KEY].toString() != JSON_GEOMETRY_POINT_VALUE)
    {
        return point;
    }

    QJsonArray jsonPoint = jsonGeometry[JSON_GEOMETRY_COORDINATES_KEY].toArray();

    point.setX(jsonPoint.at(0).toDouble());
    point.setY(jsonPoint.at(1).toDouble());

    return point;
}

QList<QVector3D> GDALManager::getMultiPointGeometry(OGRFeature *feature)
{
    QList<QVector3D> pointList;
    QJsonObject jsonGeometry = QJsonDocument::fromJson(feature->GetGeometryRef()->exportToJson()).object();

    if (jsonGeometry[JSON_GEOMETRY_TYPE_KEY].toString() != JSON_GEOMETRY_MULTIPOINT_VALUE)
    {
        return pointList;
    }

    QJsonArray jsonPointArray =  jsonGeometry[JSON_GEOMETRY_COORDINATES_KEY].toArray();

    for (int iPoint = 0; iPoint < jsonPointArray.size(); iPoint++)
    {
        QJsonArray jsonPoint = jsonPointArray.at(iPoint).toArray();
        pointList.append(QVector3D(
                             jsonPoint.at(0).toDouble(),
                             jsonPoint.at(1).toDouble(),
                             jsonPoint.at(2).toDouble()));
    }

    return pointList;
}

QList<QVector2D> GDALManager::getPolygonGeometry(OGRFeature *feature, bool ignoreClosure)
{
    QList<QVector2D> polygon;
    QJsonObject jsonGeometry = QJsonDocument::fromJson(feature->GetGeometryRef()->exportToJson()).object();

    if (jsonGeometry[JSON_GEOMETRY_TYPE_KEY].toString() != JSON_GEOMETRY_POLYGON_VALUE)
    {
        return polygon;
    }

    QJsonArray jsonPolygon = jsonGeometry[JSON_GEOMETRY_COORDINATES_KEY].toArray().at(0).toArray();
    int polygonSize = (ignoreClosure) ? jsonPolygon.size() - 1 : jsonPolygon.size();

    for (int iPoint = 0; iPoint < polygonSize; iPoint++)
    {
        QJsonArray jsonPoint = jsonPolygon.at(iPoint).toArray();
        polygon.append(QVector2D(jsonPoint.at(0).toDouble(), jsonPoint.at(1).toDouble()));
    }

    return polygon;
}

QList<QList<QVector2D> > GDALManager::getMultiPolygonGeometry(OGRFeature *feature, bool ignoreClosure)
{
    QList<QList<QVector2D>> multiPolygon;
    QJsonObject jsonGeometry = QJsonDocument::fromJson(feature->GetGeometryRef()->exportToJson()).object();

    if (jsonGeometry[JSON_GEOMETRY_TYPE_KEY].toString() != JSON_GEOMETRY_POLYGON_VALUE)
    {
        return multiPolygon;
    }

    QJsonArray jsonCurveArray = jsonGeometry[JSON_GEOMETRY_COORDINATES_KEY].toArray();

    for (int iCurve = 0; iCurve < jsonCurveArray.size(); iCurve++)
    {
        QList<QVector2D> polygon;
        QJsonArray jsonPolygon = jsonCurveArray.at(iCurve).toArray();
        int polygonSize = (ignoreClosure) ? jsonPolygon.size() - 1 : jsonPolygon.size();

        for (int iPoint = 0; iPoint < polygonSize; iPoint++)
        {
            QJsonArray jsonPoint = jsonPolygon.at(iPoint).toArray();
            polygon.append(QVector2D(jsonPoint.at(0).toDouble(), jsonPoint.at(1).toDouble()));
        }

        multiPolygon.append(polygon);
    }

    return multiPolygon;
}
