#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->processButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (m_colorDetectorCtl != NULL)
        delete m_colorDetectorCtl;
}

void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",
                        tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));

    StrategyColorDetector *stg = new StrategyColorDetector();
    m_colorDetectorCtl = new ColorDetectController((ProcessStrategy *)stg);
    if (m_colorDetectorCtl->setInputImage(fileName.toUtf8().data()))
    {
        ui->processButton->setEnabled(true);
    }

    cv::namedWindow("original");
    cv::imshow("original", m_colorDetectorCtl->getInputImage());
}

void MainWindow::on_processButton_clicked()
{
    m_colorDetectorCtl->setTargetColor(130, 190, 200);
    m_colorDetectorCtl->doProcess();
    cv::namedWindow("result");
    cv::imshow("result", m_colorDetectorCtl->getLastResult());
}
