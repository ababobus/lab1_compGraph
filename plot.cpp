#include "plot.h"
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>


Plot::Plot(QWidget *parent)
    : QWidget(parent)
{
    mAxisX.setPlot(this);
    mAxisY.setPlot(this);
    mPolylineGraph.setPlot(this);
    mAxisX.setOrientation(Qt::Horizontal);
    mAxisY.setOrientation(Qt::Vertical);
    mPolylineGraph.generate();
    //mPolyline.generateSpiral(); //генерируем спираль
    setMouseTracking(true);

}

void Plot::paintEvent(QPaintEvent *event){

    const auto startTimePoint = std::chrono::steady_clock::now();

    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    painter.setRenderHint(QPainter::Antialiasing, AntiAlising);


    mAxisX.draw(painter);
    mAxisY.draw(painter);
    mPolylineGraph.draw(painter);

    event->accept();

    const auto finalTimePoint = std::chrono::steady_clock::now();
    const auto time = std::chrono::duration<double, std::milli>(finalTimePoint - startTimePoint).count();
    const auto fps = 1 / (time/1000);

    painter.setPen(fps> 20 ? Qt::green : Qt::red);

    painter.drawText(
            rect(),
            Qt::AlignRight | Qt::AlignTop,
            QString::number(time)+ "\n" + QString::number(fps));

    painter.setPen(QPen(QBrush(Qt::magenta), 1, Qt::DotLine));
    painter.drawLine(QPoint(0, curPos.y()), QPoint(this->width(), curPos.y()));
    painter.drawLine(QPoint(curPos.x(), 0), QPoint(curPos.x(), this->height()));


    //QRect rect(QPoint(curPos.x()-30, curPos.y()+15), QPoint(curPos.x()+50, curPos.y()+45)); //верхний левый и нижний правый углы текста

    QRect textRect(QPoint(curPos.x() - 30, curPos.y() + 15), QPoint(curPos.x() + 15, curPos.y() + 45));


    double xValue = mAxisX.pixelCoordToReal(curPos.x());
       painter.drawText(textRect, Qt::AlignLeft | Qt::AlignTop, QString("X: %1").arg(xValue));

       auto result = mPolylineGraph.getYForX(curPos);

       int offsetY = 0;
       for (const auto y : result) {
           painter.drawText(textRect.translated(0, offsetY), Qt::AlignLeft | Qt::AlignBottom, QString("Y: %1").arg(y));
           offsetY += 30;
       }
}



void Plot::mousePressEvent(QMouseEvent *event){
    mMousePrevPos = event->localPos();
    event->accept();
}


void Plot::mouseMoveEvent(QMouseEvent *event){
    curPos = event->localPos();
    if (event->buttons() == Qt::LeftButton) {
        QPointF newPosition = event->localPos();

        double deltaX = mMousePrevPos.x() - newPosition.x();
        mAxisX.scroll(deltaX);

        double deltaY = mMousePrevPos.y() - newPosition.y();
        mAxisY.scroll(deltaY);

        mMousePrevPos = newPosition;
    }
    event->accept();
    update();
}


void Plot::wheelEvent(QWheelEvent *event) {
    QPointF mousePos = event->position();
    double scaleFactor;
    if (event->angleDelta().y() > 0){
         scaleFactor = 0.9;
    }
    else{
         scaleFactor = 1.1;
    }
    QPointF realPos = pixelCoordToReal(mousePos);
    scale(realPos, scaleFactor);
    event->accept();
    update();
}

QPointF Plot::realCoordToPixel(QPointF point) {
    double pixelX = mAxisX.realCoordToPixel(point.x());
    double pixelY = mAxisY.realCoordToPixel(point.y());
    return QPointF(pixelX, pixelY);
}

QPointF Plot::pixelCoordToReal(QPointF point) {
    double realX = mAxisX.pixelCoordToReal(point.x());
    double realY = mAxisY.pixelCoordToReal(point.y());
    return QPointF(realX, realY);
}

void Plot::scale(QPointF pos, double coef) {
    double realX = pos.x();
    double realY = pos.y();
    mAxisX.scale(realX, coef);
    mAxisY.scale(realY, coef);
}
void Plot::setAntiAlising(bool flag){
    AntiAlising = flag;
    update();
}

void Plot::setCount(int count){
    mPolylineGraph.generate(count);
    update();
}


void Plot::setDuglas(bool flag) {
    mPolylineGraph.setDuglasMode(flag);
    update();
}

void Plot::setWidth(int width) {
    mPolylineGraph.setWidth(width);
    update();
}
void Plot::resetAxes()
{
    mAxisX.resetBounds();
    mAxisY.resetBounds();
    update();
}



int Plot::getDuglasPointsCount()  {
    return mPolylineGraph.getDuglasPoints();
}
