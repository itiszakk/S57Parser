#ifndef GDALMANAGER_H
#define GDALMANAGER_H

#include "logger.h"
#include "ogrsf_frmts.h"

#include <QDebug>
#include <QString>
#include <QList>
#include <QVector3D>
#include <QVector2D>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


class GDALManager
{
public:
    GDALManager(Logger *log);

    bool open(const QString &filePath);
    void close();

    OGRLayer* getLayerByName(const QString &layerName);
    QList<OGRFeature*> getFeatureList(OGRLayer *layer);
    QString getFieldByName(OGRFeature* feature, const QString &fieldName);
    QString getGeometryType(OGRFeature* feature);

    QVector2D getPointGeometry(OGRFeature* feature);
    QList<QVector3D> getMultiPointGeometry(OGRFeature *feature);
    QList<QVector2D> getPolygonGeometry(OGRFeature* feature, bool ignoreClosure = true);
    QList<QList<QVector2D>> getMultiPolygonGeometry(OGRFeature* feature, bool ignoreClosure = true);

private:
    const char *JSON_GEOMETRY_TYPE_KEY = "type";
    const char *JSON_GEOMETRY_COORDINATES_KEY = "coordinates";
    const char *JSON_GEOMETRY_POLYGON_VALUE = "Polygon";
    const char *JSON_GEOMETRY_POINT_VALUE = "Point";
    const char *JSON_GEOMETRY_MULTIPOINT_VALUE = "MultiPoint";

    Logger *log;
    GDALDataset *data;
};

#endif // GDALMANAGER_H
