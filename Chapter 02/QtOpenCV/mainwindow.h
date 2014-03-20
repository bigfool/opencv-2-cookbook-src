#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //2.2 P30
    void salt(cv::Mat &image, int n);

    //2.3 P34
    void colorReduce(cv::Mat &image, int div = 64);

    //2.3.2 P36
    void colorReduce(const cv::Mat &image, cv::Mat &result, int div = 64);

    //2.4 P42 and 2.5 P42
    void colorReduceTime(cv::Mat &image, int div = 64);

    //2.6 P47
    void sharpen(const cv::Mat &image, cv::Mat &result);

    //2.6 P49
    void sharpen2D(const cv::Mat &image, cv::Mat &result);

    //2.7 P51

    //2.8

    void addROI(const cv::Mat logoImg);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_saltButton_clicked();

    void on_colorReduceButton_clicked();

    void on_cloneButton_clicked();

    void on_timeButton_clicked();

    void on_sharpenButton_clicked();

    void on_sharpen2DButton_clicked();

    void on_addLogoButton_clicked();

private:
    Ui::MainWindow *ui;
    cv::Mat m_image;
    cv::Mat m_imageClone;
    cv::Mat m_logo;
    std::string m_windowName;
    std::string m_cloneWindowName;
};

#endif // MAINWINDOW_H
