#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "controller.h"
#include "processstrategy.h"
#include "strategyhistogram1d.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    //display the image in the Label
    void displayMat(const cv::Mat &img);

private slots:
    void on_openButton_clicked();

    void on_histogramButton_clicked();

private:
    Ui::MainWindow *ui;
    Controller * m_controller;
    QString m_fileName;
};

#endif // MAINWINDOW_H