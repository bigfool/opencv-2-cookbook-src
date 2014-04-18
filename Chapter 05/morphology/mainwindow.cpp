#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->edgeButton->setEnabled(false);
    ui->cornerButton->setEnabled(false);
    ui->watershedButton->setEnabled(false);
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
    ui->edgeButton->setEnabled(true);
    ui->cornerButton->setEnabled(true);
    ui->watershedButton->setEnabled(true);
}

void MainWindow::on_edgeButton_clicked()
{
    StrategyMorphoLine *stg = new StrategyMorphoLine();
    stg->setThreshold(40);
    m_controller = Controller::getInstance((ProcessStrategy *)stg);
    if (m_controller->setInputImage(m_fileName.toUtf8().data()))
    {
        displayMat(m_controller->getInputImage());
        m_controller->doProcess();
    }

    cv::namedWindow("result");
    cv::imshow("result", m_controller->getLastResult());
}

void MainWindow::on_cornerButton_clicked()
{
    StrategyMorphCorner *stg = new StrategyMorphCorner();
    stg->setThreshold(40);
    m_controller = Controller::getInstance((ProcessStrategy *)stg);
    if (m_controller->setInputImage(m_fileName.toUtf8().data()))
    {
        displayMat(m_controller->getInputImage());
        m_controller->doProcess();
    }

    cv::namedWindow("corner result");
    cv::imshow("corner result", m_controller->getLastResult());
}

void MainWindow::on_watershedButton_clicked()
{
    StrategyWatershed *stg = new StrategyWatershed();
    m_controller = Controller::getInstance((ProcessStrategy *)stg);
    if (m_controller->setInputImage(m_fileName.toUtf8().data()))
    {
        displayMat(m_controller->getInputImage());
        m_controller->doProcess();
    }

    cv::namedWindow("watershed result");
    cv::imshow("watershed result", m_controller->getLastResult());
}
