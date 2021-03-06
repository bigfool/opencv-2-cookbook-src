#include "mainwindow.h"
#include "ui_mainwindow.h"

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
//    QPixmap pixImg = QPixmap::fromImage(qtImg);
//    this->ui->imageLabel->setPixmap(pixImg);
    this->ui->imageLabel->setPixmap(pixImg.scaled(ui->imageLabel->size(),
                                                  Qt::KeepAspectRatio));
}

void MainWindow::on_openButton_clicked()
{
     m_fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",
                        tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));
     qDebug() << "[MainWindow::on_openButton_clicked]filename: " << m_fileName;
     QPixmap pixImg(m_fileName);
     this->ui->imageLabel->setPixmap(pixImg.scaled(ui->imageLabel->size(),
                                                   Qt::KeepAspectRatio));
}

void MainWindow::on_histogramButton_clicked()
{
    StrategyHistogram1D *stg = new StrategyHistogram1D();
    m_controller = Controller::getInstance((ProcessStrategy *)stg);
    if (m_controller->setInputImage(m_fileName.toUtf8().data()))
    {
        //ui->processButton->setEnabled(true);
        displayMat(m_controller->getInputImage());
        m_controller->doProcess();
    }

    cv::namedWindow("original");
    cv::imshow("original", m_controller->getInputImage());
}

void MainWindow::on_colorHistButton_clicked()
{
    StrategyColorHistogram *stg = new StrategyColorHistogram();
    m_controller = Controller::getInstance((ProcessStrategy *)stg);
    if (m_controller->setInputImage(m_fileName.toUtf8().data()))
    {
        //ui->processButton->setEnabled(true);
        displayMat(m_controller->getInputImage());
        m_controller->doProcess();
    }

    cv::namedWindow("original");
    cv::imshow("original", m_controller->getInputImage());
}

void MainWindow::on_lutButton_clicked()
{
    StrategyLut *stg = new StrategyLut();
    m_controller = Controller::getInstance((ProcessStrategy *)stg);
    if (m_controller->setInputImage(m_fileName.toUtf8().data()))
    {
        //ui->processButton->setEnabled(true);
        displayMat(m_controller->getInputImage());
        m_controller->doProcess();
    }

    cv::namedWindow("result");
    cv::imshow("result", m_controller->getLastResult());
}

void MainWindow::on_stretchButton_clicked()
{
    StrategyStretch *stg = new StrategyStretch();
    m_controller = Controller::getInstance((ProcessStrategy *)stg);
    if (m_controller->setInputImage(m_fileName.toUtf8().data()))
    {
        //ui->processButton->setEnabled(true);
        displayMat(m_controller->getInputImage());
        m_controller->doProcess();
    }

    cv::namedWindow("stretch");
    cv::imshow("stretch", m_controller->getLastResult());
}

void MainWindow::on_equalizeButton_clicked()
{
    StrategyEqualize *stg = new StrategyEqualize();
    m_controller = Controller::getInstance((ProcessStrategy *)stg);
    if (m_controller->setInputImage(m_fileName.toUtf8().data()))
    {
        //ui->processButton->setEnabled(true);
        displayMat(m_controller->getInputImage());
        m_controller->doProcess();
    }

    cv::namedWindow("equalize");
    cv::imshow("equalize", m_controller->getLastResult());
}

void MainWindow::on_calcBlackButton_clicked()
{
    StrategyContentFinder *stg = new StrategyContentFinder();
    m_controller = Controller::getInstance((ProcessStrategy *)stg);
    if (m_controller->setInputImage(m_fileName.toUtf8().data()))
    {
        //ui->processButton->setEnabled(true);
        displayMat(m_controller->getInputImage());
        m_controller->doProcess();
    }

    cv::namedWindow("content finder");
    cv::imshow("content finder", m_controller->getLastResult());
}
