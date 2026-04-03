#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <axis.h>
#include <polyline.h>
#include <polylinegraph.h>

class Plot : public QWidget
{
public:
    Plot(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    bool AntiAlising = false;
    QPointF mMousePrevPos;
    QPointF curPos;

    Axis mAxisX;
    Axis mAxisY;
    PolylineGraph mPolylineGraph;

    void setAntiAlising(bool flag);
    void setWidth(int width);
    void setCount(int count);
    void setDuglas(bool flag);
    //void changeDuglas(double n);
    int getDuglasPointsCount();
    void resetAxes();
private:
    QPointF realCoordToPixel(QPointF p);
    QPointF pixelCoordToReal(QPointF p);
    void scale(QPointF pos, double k);
};

#endif // PLOT_H
