#include "model.h"

namespace Model
{

/* Model::Grid */

Grid::Grid(int leftBorder, int bottomBorder, int topBorder, int rightBorder, int xTicks, int yTicks)
    :leftBorder(leftBorder), bottomBorder(bottomBorder), rightBorder(rightBorder), topBorder(topBorder), xTicks(xTicks), yTicks(yTicks)
{

}

int Grid::getLeftBorder() const
{
    return leftBorder;
}

int Grid::getBottomBorder() const
{
    return bottomBorder;
}

int Grid::getRightBorder() const
{
    return rightBorder;
}

int Grid::getTopBorder() const
{
    return topBorder;
}

int Grid::getXTicks() const
{
    return xTicks;
}

int Grid::getYTicks() const
{
    return yTicks;
}

QJsonObject Grid::toJson() const
{
    QJsonObject gridObject;

    gridObject["left_border"] = leftBorder;
    gridObject["right_border"] = rightBorder;
    gridObject["bottom_border"] = bottomBorder;
    gridObject["top_border"] = topBorder;
    gridObject["xticks"] = xTicks;
    gridObject["yticks"] = yTicks;

    return gridObject;
}

/* Model::Point */

Point::Point(double x, double y)
    : x(x), y(y)
{

}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

QJsonObject Point::toJson() const
{
    QJsonObject pointObject;

    pointObject["x"] = x;
    pointObject["y"] = y;

    return pointObject;
}

/* Model::Isoline */

Isoline::Isoline(const QString &type)
    : type(type)
{

}

QString Isoline::getType() const
{
    return type;
}

QList<Point> Isoline::getContour() const
{
    return contour;
}

QList<Isoline> Isoline::getInnerIsolines() const
{
    return innerIsolines;
}

void Isoline::addContourPoint(Point point)
{
    contour.append(point);
}

void Isoline::addInnerIsoline(Isoline isoline)
{
    innerIsolines.append(isoline);
}

QJsonObject Isoline::toJson() const
{
    QJsonObject isolineObject;
    QJsonArray contourJsonArray;
    QJsonArray innerIsolinesJsonArray;

    isolineObject["type"] = type;

    for (const Point &point : contour)
    {
        contourJsonArray.append(point.toJson());
    }

    isolineObject["contour"] = contourJsonArray;

    for (const Isoline &innerIsoline : innerIsolines)
    {
        innerIsolinesJsonArray.append(innerIsoline.toJson());
    }

    isolineObject["inner_isolines"] = innerIsolinesJsonArray;

    return isolineObject;
}

/* Model::Map */

Map::Map(Grid *grid)
    : grid(grid)
{

}

void Map::addLevel(double levelHeight, Isoline isoline)
{
    levels[levelHeight].append(isoline);
}

QJsonObject Map::toJson() const
{
    QJsonObject mapObject;
    QJsonObject levelsObject;

    mapObject["grid"] = grid->toJson();

    for (const double &level : levels.keys())
    {
        QJsonArray isolinesJsonArray;

        for (const Isoline &isoline : levels[level])
        {
            isolinesJsonArray.append(isoline.toJson());
        }

        levelsObject[QString::number(level)] = isolinesJsonArray;
    }

    mapObject["levels"] = levelsObject;

    return mapObject;
}

} // namespace Model
