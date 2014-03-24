#include <opencv2/imgproc/imgproc.hpp>
#include "strategycolordetector.h"

StrategyColorDetector::StrategyColorDetector()
    : m_minDist(100)
{
    m_target[0] = 0;
    m_target[1] = 0;
    m_target[2] = 0;
}

StrategyColorDetector::~StrategyColorDetector()
{
    qDebug() << "[StrategyColorDetector::~StrategyColorDetector]~StrategyColorDetector";
}

void StrategyColorDetector::setColorDistanceThreshold(int distance)
{
    if (distance < 0)
    {
        distance = 0;
    }

    m_minDist = distance;
}

int StrategyColorDetector::getColorDistanceThreshold() const
{
    return m_minDist;
}

void StrategyColorDetector::setTargetColor(unsigned char red, unsigned char green, unsigned char blue)
{
//    m_target[2] = red;
//    m_target[1] = green;
//    m_target[0] = blue;
    cv::Mat tmp(1, 1, CV_8UC3);
    tmp.at<cv::Vec3b>(0, 0)[0] = blue;
    tmp.at<cv::Vec3b>(0, 0)[1] = green;
    tmp.at<cv::Vec3b>(0, 0)[2] = red;

    cv::cvtColor(tmp, tmp, CV_BGR2Lab);
    m_target = tmp.at<cv::Vec3b>(0, 0);
}

void StrategyColorDetector::setTargetColor(cv::Vec3b color)
{
//    m_target = color;
    cv::Mat tmp(1, 1, CV_8UC3);
    tmp.at<cv::Vec3b>(0, 0) = color;
    cv::cvtColor(tmp, tmp, CV_BGR2Lab);

    m_target = tmp.at<cv::Vec3b>(0, 0);
}

cv::Vec3b StrategyColorDetector::getTargetColor() const
{
    return m_target;
}

int StrategyColorDetector::getDistance(const cv::Vec3b& color) const
{
    return abs(color[0] - m_target[0]) +
            abs(color[1] - m_target[1]) +
            abs(color[2] - m_target[2]);
}

cv::Mat StrategyColorDetector::ProcessAlgrithmIf(const cv::Mat &image)
{
    qDebug()  << "[StrategyColorDetector::ProcessAlgrithmIf] ProcessAlgrithmIf ";
//    cv::namedWindow("debug");
//    cv::imshow("debug", image);
    m_result.create(image.rows, image.cols, CV_8U);

    cv::Mat converted;
    converted.create(image.rows, image.cols, image.type());

    cv::cvtColor(image, converted, CV_BGR2Lab); //in opencv2/imgproc/imgproc.hpp
    cv::namedWindow("debug");
    cv::imshow("debug", converted);
    cv::Mat_<cv::Vec3b>::iterator it = converted.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator itend = converted.end<cv::Vec3b>();
    cv::Mat_<uchar>::iterator itout = m_result.begin<uchar>();

    for (; it != itend; it++, itout++)
    {
        if(getDistance(*it) < m_minDist)
        {
            qDebug()  << "[StrategyColorDetector::ProcessAlgrithmIf] getDistance " << getDistance(*it);
            *itout = 255;
        }
        else
        {
            qDebug()  << "[StrategyColorDetector::ProcessAlgrithmIf] getDistance " << getDistance(*it);
            *itout = 0;
        }
    }

    cv::namedWindow("debug result");
    cv::imshow("debug result", m_result);
    return m_result;
}

void StrategyColorDetector::setTargetColorIf(unsigned char red, unsigned char green, unsigned char blue)
{
     qDebug() << QString("[StrategyColorDetector::setTargetColorIf]red = %1 green = %2 blue = %3").arg(red).arg(green).arg(blue);
    setTargetColor(red, green, blue);
}

void StrategyColorDetector::getTargetColorIf(unsigned char &red, unsigned char &green, unsigned char &blue)
{
    cv::Vec3b color = getTargetColor();
    red = color[2];
    green = color[1];
    blue = color[0];
}
