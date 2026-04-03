#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QWidget::resize(800,600);
    w1 = new Plot(this);
    w2 = new Plot(this);
    w2->setDuglas(true);
    //w1->setFixedSize(600, 250);
    //w2->setFixedSize(600, 250);
    w1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    w2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *plotLayout = new QVBoxLayout();
    plotLayout->addWidget(w1);
    plotLayout->addWidget(w2);

    QVBoxLayout *controlLayout = new QVBoxLayout();

    generateButton = new QPushButton("Генерация");
    antiAlBox = new QCheckBox("Антиалисинг");
    inwidth = new QDoubleSpinBox();
    resetAxes = new QPushButton("Сброс осей");
    num = new QDoubleSpinBox();

    inwidth->setRange(1, 20);
    inwidth->setValue(3);
    num->setRange(2, 10000);
    num->setValue(1000);

    QLabel *labelWidth = new QLabel("Толщина полинии");
    QLabel *labelNumPoints = new QLabel("Число точек");

    dugPoints = new QLabel("Число точек после прореживания");
    hhh = new QLabel();
    hhh->setText(QString::number(w2->getDuglasPointsCount()));

    controlLayout->addWidget(labelNumPoints);
    controlLayout->addWidget(num);

    controlLayout->addWidget(labelWidth);
    controlLayout->addWidget(inwidth);

    controlLayout->addWidget(antiAlBox);
    controlLayout->addWidget(generateButton);
    controlLayout->addWidget(resetAxes);
    controlLayout->addWidget(dugPoints);
    controlLayout->addWidget(hhh);

    controlLayout->addStretch();
    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addLayout(plotLayout);
    mainLayout->addLayout(controlLayout);
    setLayout(mainLayout);

    connect(generateButton, &QPushButton::clicked, this, &MainWindow::generate);
    connect(antiAlBox, &QCheckBox::toggled, this, &MainWindow::checkBoxChange);
    connect(inwidth, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::changeWidth);
    connect(resetAxes, &QPushButton::clicked, this, &MainWindow::btnResetAxes);
}
MainWindow::~MainWindow()
{
}

void MainWindow::generate() {
    int n = num->value();
    w1->setCount(n);
    w2->setCount(n);
    hhh->setText(QString::number(w2->getDuglasPointsCount()));
}

void MainWindow::checkBoxChange() {
    w1->setAntiAlising(antiAlBox->isChecked());
}

void MainWindow::changeWidth() {
    int width = inwidth->value();
    w1->setWidth(width);
    w2->setWidth(width);
}
void MainWindow::btnResetAxes()
{
    w1->mAxisX.resetBounds();
    w1->mAxisY.resetBounds();
    w2->mAxisX.resetBounds();
    w2->mAxisY.resetBounds();
    w1->update();
    w2->update();
}
