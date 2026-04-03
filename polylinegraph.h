#ifndef POLYLINEGRAPH_H
#define POLYLINEGRAPH_H

#include <QVector>
#include <QPointF>
#include <QPainter>

class Plot;

class PolylineGraph {
public:
    PolylineGraph();

    void draw(QPainter &painter) const;
    void makeDug();
    void setPlot(Plot *plot);
    //void setDugPrec(double prec);
    void generate(int nPoints = 1000);
    void setWidth(int w);
    void setDuglasMode(bool flag);
    void draw(QPainter &painter);
    double getValue(QPointF x);


    bool duglasMode = false;
    int getDuglasPoints();
    QVector<double> getYForX(QPointF point);
private:
    std::vector<QPointF> mRealCoords;
    std::vector<QPointF> mPixelCoords;
    std::vector<QPointF> dug;
    double fMax = 20;
    int start = -10;
    int end = 10;
    Plot *mPlot = nullptr;
    int n;
    int width = 3;
    double dugPrec =10;
};

#endif // POLYLINEGRAPH_H
