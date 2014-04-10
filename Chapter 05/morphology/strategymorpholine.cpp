#include "strategymorpholine.h"
#include <QDebug>

StrategyMorphoLine::StrategyMorphoLine()
    : m_threshold(-1)
{
}

StrategyMorphoLine::~StrategyMorphoLine()
{

}

cv::Mat StrategyMorphoLine::getEdges(const cv::Mat &image)
{
    cv::Mat result;

    try
    {
        //获得边缘的关键函数调用
        cv::morphologyEx(image, result, cv::MORPH_GRADIENT, cv::Mat());
    }
    catch(cv::Exception e)
    {
        qDebug() << "[StrategyMorphoLine::getEdges]exception: "
                 <<  QString::fromStdString(e.msg);
    }

    //二值化图像
    applyThreshold(result);
    return result;
}

void StrategyMorphoLine::applyThreshold(cv::Mat &result)
{
    if (m_threshold > 0)
    {
        cv::threshold(result, result, m_threshold, 255, cv::THRESH_BINARY);
    }
    else
    {
        qDebug() << "[StrategyMorphoLine::applyThreshold] threshold value < 0";
    }
}

cv::Mat StrategyMorphoLine::ProcessAlgrithmIf(const cv::Mat &image)
{
    return getEdges(image);
}
