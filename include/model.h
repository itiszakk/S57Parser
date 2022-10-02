#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>

namespace Model
{

class Grid
{

public:
    Grid(int leftBorder, int bottomBorder, int rightBorder, int topBorder, int xTicks, int yTicks);

    int getLeftBorder() const;
    int getBottomBorder() const;
    int getRightBorder() const;
    int getTopBorder() const;
    int getXTicks() const;
    int getYTicks() const;

    QJsonObject toJson() const;

private:
    int leftBorder;
    int bottomBorder;
    int rightBorder;
    int topBorder;
    int xTicks;
    int yTicks;
};

class Point
{

public:
    Point(double x, double y);

    double getX() const;
    double getY() const;

    QJsonObject toJson() const;

private:
    double x;
    double y;
};


class Isoline
{

public:
    Isoline(const QString &type);

    QString getType() const;
    QList<Point> getContour() const;
    QList<Isoline> getInnerIsolines() const;

    void addContourPoint(Point point);
    void addInnerIsoline(Isoline isoline);

    QJsonObject toJson() const;

private:
    QString type;
    QList<Point> contour;
    QList<Isoline> innerIsolines;
};


class Map
{

public:
    Map(Grid *grid);

    void addLevel(double levelHeight, Isoline isoline);

    QJsonObject toJson() const;

private:
    Grid *grid;
    QMap<double, QList<Isoline>> levels;

};

} // namespace Model

#endif // MODEL_H
