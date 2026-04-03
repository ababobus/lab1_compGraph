#include "axis.h"
#include "plot.h"
void Axis::setPlot(Plot *plot)
{
    mPlot = plot;
}

void Axis::draw(QPainter &painter){ //метод отрисовки оси
    painter.setPen(Qt::white);
    QString lowerStr = QString::number(mLower); //преобразование в строковый тип данных
    QString upperStr = QString::number(mUpper);

    QPaintDevice *device = painter.device();//объявление девайса для отрисовки
    double offset = 12;//смещение для текста


    if (mOrientation == Qt::Horizontal){ //для горизонтальной оси
        QRect rect(offset, 0, device->width() - offset, device->height());
        painter.drawText(
                    rect,
                    Qt::AlignLeft | Qt::AlignBottom,
                    lowerStr
                    );
        painter.drawText(
                    rect,
                    Qt::AlignRight | Qt::AlignBottom,
                    upperStr
                    );
    }else{
        QRect rect(0, 0, device->width(), device->height() - offset);
        painter.drawText(
                    rect,
                    Qt::AlignRight| Qt::AlignTop,
                    lowerStr
                    );
        painter.drawText(
                    rect,
                    Qt::AlignLeft | Qt::AlignTop,
                    upperStr
                    );
    }

}

double Axis::realCoordToPixel(double real) const{
    if (mOrientation == Qt::Horizontal){
        const double pixelLengthPerReal = mPlot->width()/(mUpper - mLower);
        const double pixelCoord = 0 +(real - mLower)*pixelLengthPerReal;
        return pixelCoord   ;
    }
    else{ //для вертик оси
        const double pixelLengthPerReal = mPlot->height()/(mUpper - mLower);
        const double pixelCoord = 0 +(mUpper-real)*pixelLengthPerReal;
        return pixelCoord;
    }
}
double Axis::pixelCoordToReal(double x) const {
    if (mOrientation == Qt::Horizontal) {
        double pixelFraction = x / mPlot->width();
        double realRange = mUpper - mLower;
        double realCoord = pixelFraction * realRange + mLower;
        return realCoord;
    } else {
        double pixelFraction = x / mPlot->height();
        double realRange = mUpper - mLower;
        double realCoord = mUpper - pixelFraction * realRange;
        return realCoord;
    }
}

void Axis::scroll(double pixelDelta){ //длz перемещения оси
    const double realLengthPerPixel = mOrientation == Qt::Horizontal ?  (mUpper - mLower) / mPlot->width()
                                             :(mLower - mUpper) / mPlot->height();
    const double realDelta = pixelDelta*realLengthPerPixel;//смещение

    mLower += realDelta;
    mUpper += realDelta;
}
void Axis::scale(double pos, double k) {//масштабирование оси
    mLower += (mLower - pos) * (k - 1);
    mUpper += (mUpper - pos) * (k - 1);
}

void Axis::resetBounds()
{
    mLower = -10;
    mUpper = 10;
}


