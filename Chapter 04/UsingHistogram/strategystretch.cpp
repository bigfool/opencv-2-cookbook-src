#include "strategystretch.h"
#include <opencv2/imgproc/imgproc.hpp>

StrategyStretch::StrategyStretch()
{
}

StrategyStretch::~StrategyStretch()
{

}

cv::Mat StrategyStretch::ProcessAlgrithmIf(const cv::Mat &image)
{
    return strech(image, 100);
}

cv::Mat StrategyStretch::strech(const cv::Mat &image, int minValue)
{
    StrategyHistogram1D hist1D;
    cv::MatND hist = hist1D.getHistogram(image);

    //寻找直方图的左端
    int imin = 0;
    for (; imin < hist1D.getHistSize(); imin++)
    {
        if (hist.at<float>(imin) > minValue)
            break;
    }

    //寻找直方图的右端
    int imax = hist1D.getHistSize() - 1;
    for (; imax >= 0; imax--)
    {
        if (hist.at<float>(imax) > minValue)
            break;
    }

    //创建查找表
    int dim(256);
    cv::Mat lookup(1, &dim, CV_8U);
    //填充查找表
    for (int i = 0; i < 256; i++)
    {
        if (i < imin)
        {
            lookup.at<uchar>(i) = 0;
        }
        else if (i > imax)
        {
            lookup.at<uchar>(i) = 255;
        }
        else
        {
            lookup.at<uchar>(i) = static_cast<uchar>(255.0 * (i - imin)/(imax-imin) + 0.5);
        }
    }

    cv::Mat result;
    cv::LUT(image, lookup, result); //应用查找表

    //扩展后的直方图
    hist1D.getHistogramImage(result);

    return result;
}
