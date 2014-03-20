#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_windowName = "output";
    m_cloneWindowName = "clone output";
    m_logo = cv::imread("logo.bmp", 0);

    ui->pushButton_2->setEnabled(false);
    ui->saltButton->setEnabled(false);
    ui->colorReduceButton->setEnabled(false);
    ui->cloneButton->setEnabled(false);
    ui->timeButton->setEnabled(false);
    ui->timeLabel->setHidden(true);
    ui->sharpenButton->setEnabled(false);
    ui->sharpen2DButton->setEnabled(false);
    ui->addLogoButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",
                        tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));

    m_image = cv::imread((fileName.toUtf8().data()));
//    cv::namedWindow("Original Image");
//    cv::imshow("Original Image", m_image);
    cv::namedWindow(m_windowName);
    cv::imshow(m_windowName, m_image);
    if (m_image.data)
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
        ui->saltButton->setEnabled(true);
        ui->colorReduceButton->setEnabled(true);
        ui->cloneButton->setEnabled(true);
        ui->timeButton->setEnabled(true);
        ui->sharpenButton->setEnabled(true);
        ui->sharpen2DButton->setEnabled(true);
        ui->addLogoButton->setEnabled(true);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    cv::flip(m_image, m_image, 1);
//    cv::namedWindow("Output Image");
//    cv::imshow("Output Image", m_image);
    cv::imshow(m_windowName, m_image);
}

void MainWindow::salt(cv::Mat &image, int n)
{
    for (int k = 0; k < n; k++)
    {
        int i = qrand() % image.cols;
        int j = qrand() % image.rows;

        if (image.channels() == 1)
        {
            image.at<uchar>(j, i) = 255;
        }
        else if (image.channels() == 3)
        {
            image.at<cv::Vec3b>(j, i)[0] = 255;
            image.at<cv::Vec3b>(j, i)[1] = 255;
            image.at<cv::Vec3b>(j, i)[2] = 255;
        }
    }
}

void MainWindow::on_saltButton_clicked()
{
    int n = qrand() % 3000;
    salt(m_image, n);
    cv::imshow(m_windowName, m_image);
}

void MainWindow::colorReduce(cv::Mat &image, int div)
{
    int nl = image.rows; //rows
    int nc = image.cols * image.channels();

    if (image.isContinuous())
    {
        nc = nc * nl;
        nl = 1;
    }

    for (int j = 0; j < nl; j++)
    {
        uchar *data = image.ptr<uchar>(j);
        for (int i = 0; i < nc; i++)
        {
//            data[i] = data[i] / div * div + div / 2;

            // for speed
            uchar mask = 0xFF << div;
            data[i] = (data[i] & mask) + div / 2;
        }

        //or
//        *data++ = *data / div * div + div / 2;
    }
}



void MainWindow::on_colorReduceButton_clicked()
{
    colorReduce(m_image);
    cv::imshow(m_windowName, m_image);
}

void MainWindow::colorReduce(const cv::Mat &image, cv::Mat &result, int div)
{
    result.create(image.rows, image.cols, image.type());
    result = image.clone();
    colorReduce(result);
}

void MainWindow::on_cloneButton_clicked()
{
    colorReduce(m_image, m_imageClone);

    if (!m_imageClone.empty())
    {
        cv::namedWindow(m_cloneWindowName);
        cv::imshow(m_cloneWindowName, m_imageClone);
    }
}

void MainWindow::colorReduceTime(cv::Mat &image, int div)
{
    double duration;
    duration = static_cast<double>(cv::getTickCount());

    cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator itEnd = image.end<cv::Vec3b>();
    for (; it != itEnd; ++it)
    {
        (*it)[0] = (*it)[0] / div * div + div / 2;
        (*it)[1] = (*it)[1] / div * div + div / 2;
        (*it)[2] = (*it)[2] / div * div + div / 2;
    }

    duration = static_cast<double>(cv::getTickCount()) - duration;
    duration /= cv::getTickFrequency(); //ms
    QString time = QString("%1").arg(duration);
    qDebug() << "[MainWindow::colorReduceTime] duration is " << time;
    ui->timeLabel->setText("Times: " + time + "ms");
    ui->timeLabel->setHidden(false);
}

void MainWindow::on_timeButton_clicked()
{
    colorReduceTime(m_image);
    cv::imshow(m_windowName, m_image);
}

void MainWindow::sharpen(const cv::Mat &image, cv::Mat &result)
{
    result.create(image.size(), image.type());
//    result = image.clone();

    const int nChannels = image.channels();

    for (int j = 1; j < image.rows - 1; j++)
    {
        const uchar *previous = image.ptr<const uchar>(j-1);
        const uchar *current = image.ptr<const uchar>(j);
        const uchar *next = image.ptr<const uchar>(j+1);

        uchar * output = result.ptr<uchar>(j);

        for(int i = nChannels; i < nChannels * (image.cols - 1); i++)
        {
            *output++ = cv::saturate_cast<uchar>(
                        5 * current[i] - current[i+nChannels]
                        - current[i+nChannels] - previous[i] - next[i]);
        }
    }

    result.row(0).setTo(cv::Scalar(0));
    result.row(result.rows-1).setTo(cv::Scalar(0));
    result.col(0).setTo(cv::Scalar(0));
    result.col(result.cols-1).setTo(cv::Scalar(0));
}

void MainWindow::on_sharpenButton_clicked()
{
    sharpen(m_image, m_imageClone);
    if (!m_imageClone.empty())
    {
        cv::namedWindow(m_cloneWindowName);
        cv::imshow(m_cloneWindowName, m_imageClone);
    }
}

void MainWindow::sharpen2D(const cv::Mat &image, cv::Mat &result)
{
    // init kernel
    cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0));
    kernel.at<float>(1, 1) = 5.0;
    kernel.at<float>(0, 1) = -1.0;
    kernel.at<float>(2, 1) = -1.0;
    kernel.at<float>(1, 0) = -1.0;
    kernel.at<float>(1, 2) = -1.0;

    cv::filter2D(image, result, image.depth(), kernel); // in OpenCV 1.0
}

void MainWindow::on_sharpen2DButton_clicked()
{
    sharpen2D(m_image, m_imageClone);
    if (!m_imageClone.empty())
    {
        cv::namedWindow(m_cloneWindowName);
        cv::imshow(m_cloneWindowName, m_imageClone);
    }
}

void MainWindow::addROI(const cv::Mat logoImg)
{
    cv::Mat imageROI;
    imageROI = m_image(cv::Rect(10, 10, logoImg.cols, logoImg.rows));
    logoImg.copyTo(imageROI, m_logo);
//    cv::addWeighted(imageROI, 1.0, logoImg, 0.3, 0., imageROI);
    cv::namedWindow(m_windowName);
    cv::imshow(m_windowName, m_image);

//    cv::imshow(m_windowName, m_logo);
    qDebug() << "[MainWIndow::addROI] done";
}

void MainWindow::on_addLogoButton_clicked()
{
    addROI(m_logo);
//    cv::namedWindow(m_windowName);
//    cv::imshow(m_windowName, m_image);
}
