#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "context.h"
#include "processstrategy.h"
#include "strategycolordetector.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_processButton_clicked()
{
    cv::Mat image = cv::imread("psb.jpg");
    if (!image.data)
    {
        qDebug() << "[MainWindow::on_processButton_clicked] read image error";
    }
    StrategyColorDetector *ps;
    ps = new StrategyColorDetector();
    ps->setTargetColor(130, 190, 230);

    Context *cont = new Context((ProcessStrategy *) ps);
    cv::Mat result = cont->doProcess(image);
//    if (cont != NULL)
//    {
//        delete cont;
//    }
    cv::namedWindow("original");
    cv::imshow("original", image);

    cv::namedWindow("original");
    cv::imshow("result", result);
}
