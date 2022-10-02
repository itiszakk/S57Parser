#include "s57_parser.h"

S57Parser::S57Parser(const QString &inputFilePath, const QString &outputFilePath, Logger *log)
    : inputFilePath(inputFilePath)
    , outputFilePath(outputFilePath)
    , coordinateOffset(0.0, 0.0)
    , maxCoordinate(0.0, 0.0)
    , log(log)
    , gdal(nullptr)
    , grid(nullptr)
    , map(nullptr)
{

}

S57Parser::~S57Parser()
{
    delete gdal;
    delete grid;
    delete map;
}

void S57Parser::parse()
{
    gdal = new GDALManager(log);

    if (!gdal->open(inputFilePath))
    {
        return;
    }

    grid = new Model::Grid(0, 0, 40000, 40000, 400, 400);
    map = new Model::Map(grid);

    OGRLayer *coverageLayer = gdal->getLayerByName(COVERAGE_LAYER_ACRONYM);
    OGRLayer *waterLayer = gdal->getLayerByName(WATER_LAYER_ACRONYM);
    OGRLayer *surfaceLayer = gdal->getLayerByName(SURFACE_LAYER_ACRONYM);
    OGRLayer *soundingLayer = gdal->getLayerByName(SOUNDING_LAYER_ACRONYM);

    setCoordinateOffset(coverageLayer);

    waterLayerHandler(waterLayer);
    surfaceLayerHandler(surfaceLayer);
    soundingLayerHandler(soundingLayer);

    gdal->close();

    if (!saveOutputJson())
    {
        return;
    }

    log->info("Parsing completed");
}

void S57Parser::waterLayerHandler(OGRLayer *waterLayer)
{
    if (waterLayer == nullptr)
    {
        return;
    }

    log->info(QString("Handling '%1' layer").arg(waterLayer->GetName()));

    for (OGRFeature *feature : gdal->getFeatureList(waterLayer))
    {
        Model::Isoline isoline = Model::Isoline(WATER_ISOLINE_TYPE);
        double waterMinDepth = gdal->getFieldByName(feature, WATER_MIN_DEPTH).toDouble();

        for (const QList<QVector2D> &polygon : gdal->getMultiPolygonGeometry(feature))
        {
            for (QVector2D point : polygon)
            {
                isoline.addContourPoint(getAdjustedPoint(point));
            }
        }

        map->addLevel(waterMinDepth, isoline);
    }
}

void S57Parser::surfaceLayerHandler(OGRLayer *surfaceLayer)
{
    if (surfaceLayer == nullptr)
    {
        return;
    }

    log->info(QString("Handling '%1' layer").arg(surfaceLayer->GetName()));

    for (OGRFeature *feature : gdal->getFeatureList(surfaceLayer))
    {
        Model::Isoline isoline = Model::Isoline(SURFACE_ISOLINE_TYPE);

        /* Land area (LNDARE) allows several geometry primitives */

        if (gdal->getGeometryType(feature) == GEOMETRY_POINT)
        {
            QVector2D point = gdal->getPointGeometry(feature);
            isoline.addContourPoint(getAdjustedPoint(point));
        }
        else if (gdal->getGeometryType(feature) == GEOMETRY_POLYGON)
        {
            for (QVector2D point : gdal->getPolygonGeometry(feature))
            {
                isoline.addContourPoint(getAdjustedPoint(point));
            }
        }

        map->addLevel(SURFACE_LEVEL, isoline);
    }
}

void S57Parser::soundingLayerHandler(OGRLayer *soundingLayer)
{
    if (soundingLayer == nullptr)
    {
        return;
    }

    log->info(QString("Handling '%1' layer").arg(soundingLayer->GetName()));

    for (OGRFeature *feature : gdal->getFeatureList(soundingLayer))
    {
        for (QVector3D point : gdal->getMultiPointGeometry(feature))
        {
            Model::Isoline isoline = Model::Isoline(WATER_ISOLINE_TYPE);
            isoline.addContourPoint(getAdjustedPoint(point.toVector2D()));
            map->addLevel(point.z(), isoline);
        }
    }
}

void S57Parser::setCoordinateOffset(OGRLayer *coverageLayer)
{
    if (coverageLayer == nullptr)
    {
        return;
    }

    log->info("Calculating coordinates offset");

    double minInnerX = MAX_LONGITUDE;
    double minInnerY = MAX_LATITUDE;
    double maxInnerX = MIN_LONGITUDE;
    double maxInnerY = MIN_LATITUDE;

    double minOuterX = MAX_LONGITUDE;
    double minOuterY = MAX_LATITUDE;
    double maxOuterX = MIN_LONGITUDE;
    double maxOuterY = MIN_LATITUDE;

    // Consists of inner coverage feature and outer coverage feature
    QList<OGRFeature*> features = gdal->getFeatureList(coverageLayer);

    for (QVector2D point : gdal->getPolygonGeometry(features.at(0)))
    {
        if (point.x() < minInnerX) minInnerX = point.x();
        if (point.y() < minInnerY) minInnerY = point.y();
        if (point.x() > maxInnerX) maxInnerX = point.x();
        if (point.y() > maxInnerY) maxInnerY = point.y();
    }

    for (QVector2D point : gdal->getPolygonGeometry(features.at(1)))
    {
        if (point.x() < minOuterX) minOuterX = point.x();
        if (point.y() < minOuterY)  minOuterY = point.y();
        if (point.x() > maxOuterX) maxOuterX = point.x();
        if (point.y() > maxOuterY)  maxOuterY = point.y();
    }

    if (minInnerX < minOuterX) std::swap(minInnerX, minOuterX);
    if (minInnerY < minOuterY) std::swap(minInnerY, minOuterY);
    if (maxInnerX > maxOuterX) std::swap(maxInnerX, maxOuterX);
    if (maxInnerY > maxOuterY) std::swap(maxInnerY, maxOuterY);

    if (minInnerX < 0) coordinateOffset.setX(-minInnerX);
    if (minInnerY < 0) coordinateOffset.setY(-minInnerY);

    maxCoordinate.setX(maxInnerX);
    maxCoordinate.setY(maxInnerY);
}

Model::Point S57Parser::getAdjustedPoint(QVector2D point)
{
    Model::Point adjustedPoint = Model::Point(
                COORDINATE_SCALE * (point.x() + coordinateOffset.x()) / (maxCoordinate.x() + coordinateOffset.x()),
                COORDINATE_SCALE * (point.y() + coordinateOffset.y()) / (maxCoordinate.y() + coordinateOffset.y()));

    return adjustedPoint;
}

bool S57Parser::saveOutputJson(bool compact)
{
    QJsonDocument jsonDocument;
    jsonDocument.setObject(map->toJson());

    QJsonDocument::JsonFormat format = (compact)
            ? QJsonDocument::JsonFormat::Compact
            : QJsonDocument::JsonFormat::Indented;

    QByteArray data = jsonDocument.toJson(format);

    log->info(QString("Creating output file '%1'").arg(outputFilePath));

    QFile outputFile = QFile(outputFilePath);

    if (!outputFile.open(QIODevice::WriteOnly))
    {
        log->error(QString("Access to '%1' denied").arg(outputFilePath));
        return false;
    }

    outputFile.write(data);
    outputFile.close();

    return true;
}
