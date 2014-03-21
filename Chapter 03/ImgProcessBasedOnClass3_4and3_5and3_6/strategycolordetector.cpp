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
    m_target[2] = red;
    m_target[1] = green;
    m_target[0] = blue;
}

void StrategyColorDetector::setTargetColor(cv::Vec3b color)
{
    m_target = color;
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
    m_result.create(image.rows, image.cols, CV_8U);

    cv::Mat_<cv::Vec3b>::const_iterator it = image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::const_iterator itend = image.end<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator itout = m_result.begin<cv::Vec3b>();

    for (; it != itend; it++, itout++)
    {
        if(getDistance(*it) < m_minDist)
        {
            *itout = 255;
        }
        else
        {
            *itout = 0;
        }
    }

    return m_result;
}

void StrategyColorDetector::setTargetColorIf(unsigned char red, unsigned char green, unsigned char blue)
{
     qDebug() << QString("[ProcessStrategy::setTargetColorIf]red = %1 green = %2 blue = %3").arg(red).arg(green).arg(blue);
    setTargetColor(red, green, blue);
}

void StrategyColorDetector::getTargetColorIf(unsigned char &red, unsigned char &green, unsigned char &blue)
{
    cv::Vec3b color = getTargetColor();
    red = color[2];
    green = color[1];
    blue = color[0];
}
