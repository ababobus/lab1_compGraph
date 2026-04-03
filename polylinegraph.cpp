#include "polylinegraph.h"

#include <QDebug>
#include <cmath>
#include <QTransform>
#include <ctime>

#include <plot.h>

PolylineGraph::PolylineGraph() {}

class Plot;
double distance(const QPointF &start,const QPointF &end, const QPointF &point)
{
    double A = point.y() - start.y();
    double B = start.x() - point.x();
    double C = point.x() * start.y() - start.x() * point.y();

    double dist = std::abs(A * end.x() + B * end.y() + C) / std::sqrt(A * A + B * B);
    return dist;
}
double findMax(std::vector<QPointF> points, double begin, double end) {
    double maxIndex = begin;
    double maxDist = 0;
    double iter = begin;
    while (iter != end) {
        double dist = distance(points[iter], points[begin], points[end]);
        if (dist > maxDist) {
            maxIndex = iter;
            maxDist = dist;
        }
        iter++;
    }
    return maxIndex;
}

void duglas(std::vector<QPointF>& pointsResult, std::vector<QPointF>& pointsSource, double begin, double end, double tolerance) {
    double maxIndex = findMax(pointsSource, begin, end);
    double maxDist = distance(pointsSource[maxIndex], pointsSource[begin], pointsSource[end]);
     if (maxDist > tolerance) {
        duglas(pointsResult, pointsSource, begin, maxIndex, tolerance);
        duglas(pointsResult, pointsSource, maxIndex, end, tolerance);
     }
     else {
        pointsResult.push_back(pointsSource[begin]);
//        pointsResult.push_back(pointsSource[end]);
     }
 }

void PolylineGraph::setPlot(Plot *plot)
{
    mPlot = plot;
}
//void PolylineGraph::setDugPrec(double prec) {
//    dugPrec = prec;
//    makeDug();
//}

void PolylineGraph::setDuglasMode(bool flag) {
    duglasMode = flag;
    generate();

}

void PolylineGraph::setWidth(int w) {
    width = w;
}

void PolylineGraph::makeDug() {
    dug.clear();
    if (duglasMode==true) {//&&dugprec!=0
        duglas(dug, mRealCoords, 0, mRealCoords.size()-1, dugPrec);
        dug.push_back(mRealCoords.back());
    }
    else {
        dug = mRealCoords;
    }
}


void PolylineGraph::generate(int nPoints)
{
    mRealCoords.clear();
    mPixelCoords.clear();
    dug.clear();

    srand(time(NULL));
    n = nPoints;
    mRealCoords.resize(nPoints);

    double deltaF = static_cast<double>(end-start)/ (nPoints - 1);

    for (int i = 0; i < nPoints; ++i)
    {
        //double x = start + static_cast<double>(std::rand()) / RAND_MAX * (end - start);
        //double y = sin(x*x)*6;
        double t = start +i*deltaF;
        double h = 8;
        double r = 5;
        double x = r*t-h*sin(t);
        double y = r-h*cos(t);

        //double x = -10 + deltaF*i;
        //double y = sin(x);
        //if(y<0){y=2;}
        //QTransform rotation;
        //rotation.rotate(90);
        //QPointF originalPoint(x, y);
        //QPointF rotatedPoint = rotation.map(originalPoint);

        mRealCoords[i].setX(x);
        mRealCoords[i].setY(y);
    }
    makeDug();
}
void PolylineGraph::draw(QPainter &painter)
{
    mPixelCoords.resize(dug.size());
    //QRect rect(QPoint(20, 20), QPoint(120, 60));
    painter.setPen(Qt::white);
    //QString s = "num of points:";
    //painter.drawText(rect, Qt::AlignLeft|Qt::AlignTop, s);
    //painter.drawText(rect, Qt::AlignRight|Qt::AlignTop, QString::number(dug.size()));

    for (int i = 0, size = dug.size(); i < size; ++i)
    {
        double pixelX = mPlot->mAxisX.realCoordToPixel(dug[i].x());
        double pixelY = mPlot->mAxisY.realCoordToPixel(dug[i].y());
        mPixelCoords[i].rx() = pixelX;
        mPixelCoords[i].ry() = pixelY;
    }

    double point1x = mPlot->mAxisX.realCoordToPixel(mPlot->mAxisX.mLower);
    double point1y = mPlot->mAxisY.realCoordToPixel(0);
    double point2x = mPlot->mAxisX.realCoordToPixel(mPlot->mAxisX.mUpper);
    double point2y = mPlot->mAxisY.realCoordToPixel(0);
    painter.setPen(QPen(QBrush(Qt::yellow), width));
    painter.drawLine(QPoint(point1x, point1y), QPoint(point2x, point2y));

    point1x = mPlot->mAxisX.realCoordToPixel(0);
    point1y = mPlot->mAxisY.realCoordToPixel(mPlot->mAxisY.mLower);
    point2x = mPlot->mAxisX.realCoordToPixel(0);
    point2y = mPlot->mAxisY.realCoordToPixel(mPlot->mAxisY.mUpper);
    painter.drawLine(QPoint(point1x, point1y), QPoint(point2x, point2y));

    painter.setPen(QPen(QBrush(Qt::blue), width));
    painter.drawPolyline(mPixelCoords.data(), mPixelCoords.size());

}

QVector<double> PolylineGraph::getYForX(QPointF point)
{
    QVector<double> results;
    double x = mPlot->mAxisX.pixelCoordToReal(point.x());

    for (int i = 0; i <  mRealCoords.size() - 1; ++i) {
        double x1 = mRealCoords[i].x();
        double y1 = mRealCoords[i].y();
        double x2 = mRealCoords[i + 1].x();
        double y2 = mRealCoords[i + 1].y();

        if ((x1 <= x && x <= x2) || (x2 <= x && x <= x1)) {
            double y = y1 + (x - x1) * (y2 - y1) / (x2 - x1);
            results.append(y);
        }
    }

    return results;
}

int PolylineGraph::getDuglasPoints(){
    return dug.size();
}
