#include "strategyequalize.h"
#include <opencv2/imgproc/imgproc.hpp>

StrategyEqualize::StrategyEqualize()
{
}

StrategyEqualize::~StrategyEqualize()
{

}

cv::Mat StrategyEqualize::ProcessAlgrithmIf(const cv::Mat &image)
{
    return equalize(image);
}

cv::Mat StrategyEqualize::equalize(const cv::Mat &image)
{
    cv::Mat result;
    result.create(image.rows, image.cols, image.type());

    try
    {
         cv::equalizeHist(image, result);
    }
    catch (cv::Exception e)
    {
        qDebug() << "[StrategyEqualize::equalize] exception: " << QString::fromStdString(e.msg);
    }
    return result;
}
