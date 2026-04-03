#ifndef AXIS_H
#define AXIS_H

#include <QPainter>
#include <QPointer>
class Plot;
class Axis
{
public:
    void setPlot(Plot *plot);
    void draw(QPainter &painter);
    void setOrientation(Qt::Orientation v){
        mOrientation = v;
    }
    double realCoordToPixel(double real) const;
    double pixelCoordToReal(double x) const;
    void scroll(double pixelDelta);;
    void scale(double pos, double k);
    double mLower = -10;
    double mUpper = 10;

    void resetBounds();
protected:
    QPointer<Plot> mPlot;

    double minX, maxX; // Минимальные и максимальные значения по X
    double minY, maxY;
    Qt::Orientation mOrientation = Qt::Horizontal;
};

#endif
