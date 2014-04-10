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
