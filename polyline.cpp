#include "polyline.h"
#include "plot.h"
#include <cmath>

void Polyline::setPlot(Plot *plot){
    mPlot = plot;
}
void Polyline::generateSpiral(int nPoints, double numberCycle){
    mRealCoords.resize(nPoints); //изменяем размер контейнера для реальных координат
    //контейнер это динамический массив реальных координат
    //здесь мы генерируем реальные координаты
    double a = 0.2; //для спирали
    double b = 0.15;
    double fMax = 2*std::acos(-1)*numberCycle; //макс. значени угла
    double deltaF = fMax/(nPoints -1); //шаг угла

    for (int i =0;i < nPoints;++i){
        //логарифмическая спираль
        double f = i*deltaF; //текущий угол
        double r = a*std::exp(b*f); //радиус спирали
        double x = r*std::cos(f);
        double y = r*std::sin(f);

        mRealCoords[i].setX(x); //устанавливаем х и у
        mRealCoords[i].setY(y);
    }
}

void Polyline::draw(QPainter &painter){
    mPixelCoords.resize(mRealCoords.size()); //изменяем размер контейнера для пиксельных координат
    for (int i = 0, size = mRealCoords.size(); i<size;++i){
        double pixelX = mPlot->mAxisX.realCoordToPixel(mRealCoords[i].x());
        //realCoordToPixel(mRealCoords[i].x()) передаем реальные координаты в метод класса AXISи преобразовываем в пискельные
        double pixelY = mPlot->mAxisY.realCoordToPixel(mRealCoords[i].y());
        mPixelCoords[i].rx() = pixelX;
        mPixelCoords[i].ry() = pixelY;
    }

    painter.setPen(QPen(QBrush(Qt::red), 5));//цвет и толщина
    painter.drawPolyline(mPixelCoords.data(), mPixelCoords.size());
}
