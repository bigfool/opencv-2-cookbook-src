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
}

void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",
                        tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));

    StrategyColorDetector *stg = new StrategyColorDetector();
//    m_colorDetectorCtl = new ColorDetectController((ProcessStrategy *)stg);
    m_colorDetectorCtl = ColorDetectController::getInstance((ProcessStrategy *)stg);
    if (m_colorDetectorCtl->setInputImage(fileName.toUtf8().data()))
    {
        ui->processButton->setEnabled(true);
        displayMat(m_colorDetectorCtl->getInputImage());
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

void MainWindow::displayMat(const cv::Mat &img)
{
    QImage qtImg = QImage((const unsigned char *)img.data, img.cols, img.rows,
                          img.step, QImage::Format_RGB888);

    if (qtImg.isNull())
    {
        QVector<QRgb> colorTable;
        for (int i = 0; i < 256; i++)
        {
            colorTable.push_back(qRgb(i, i, i));
        }

        qtImg = QImage((const unsigned char *)img.data, img.cols, img.rows,
                       QImage::Format_Indexed8);
        qtImg.setColorTable(colorTable);
    }

    QPixmap pixImg = QPixmap::fromImage(qtImg.rgbSwapped());
    this->ui->imageLabel->setPixmap(pixImg.scaled(ui->imageLabel->size(),
                                                  Qt::KeepAspectRatio));
}

void MainWindow::setColor()
{
    QColor color = QColorDialog::getColor(Qt::green, this);
    if (color.isValid())
    {
        m_colorDetectorCtl->setTargetColor(color.red(), color.green(), color.blue());
    }
}

void MainWindow::on_selectColorButton_clicked()
{
    setColor();
}
