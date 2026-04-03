#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <plot.h>
#include <QLabel>
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QWidget *m = new QWidget();
    QVBoxLayout *layout;
    QVBoxLayout* layout2;
    QPushButton* generateButton;
    QPushButton* resetAxes;
    QCheckBox* antiAlBox;
    QLineEdit *setCount;
    QLabel *dugPoints;
    QLabel *hhh;

    //QLineEdit *inwidth;

    Plot* w1;
    Plot* w2;
    QDoubleSpinBox* inwidth;
    //QDoubleSpinBox* induglas;
    QDoubleSpinBox* num;
    void generate();
    void checkBoxChange();
    void changeWidth();
    void btnResetAxes();
};

#endif // MAINWINDOW_H
