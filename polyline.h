#ifndef POLYLINE_H
#define POLYLINE_H

#include <QPointer>
#include <QPainter>
class Plot; //forward declaration

class Polyline
{
public:
    void setPlot(Plot *plot);
    void generateSpiral(int nPoints = 100000, double nymberCycle=10);
    void draw(QPainter &painter);
    QVector<double> getYForX(double x);
protected:
    QPointer<Plot> mPlot;
    int n;
    std::vector<QPointF> mRealCoords;//котейнеры
    std::vector<QPointF> mPixelCoords;
};

#endif // POLYLINE_H
