#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include "colordetectcontroller.h"
#include "processstrategy.h"
#include "strategycolordetector.h"

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
    void setColor();

private slots:
    void on_openButton_clicked();

    void on_processButton_clicked();

    void on_selectColorButton_clicked();

    void on_distanceThresholdSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    ColorDetectController *m_colorDetectorCtl;
};

#endif // MAINWINDOW_H
