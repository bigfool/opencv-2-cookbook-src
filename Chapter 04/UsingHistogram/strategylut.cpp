#include "strategylut.h"
#include <opencv2/imgproc/imgproc.hpp>

StrategyLut::StrategyLut()
{
    int dim = 256;
    m_lookup.create(1, dim, CV_8U);
    for (int i = 0; i < 256; i++)
    {
        m_lookup.at<uchar>(i) = 255 - i;
    }
}

StrategyLut::~StrategyLut()
{

}

cv::Mat StrategyLut::ProcessAlgrithmIf(const cv::Mat &image)
{
    int dim[1] = {256};
    cv::Mat lookup(1, dim, CV_8U);
    for (int i = 0; i < 256; i++)
    {
        lookup.at<uchar>(i) = 255 - i;
    }
    return applyLookup(image, m_lookup);
}

cv::Mat StrategyLut::applyLookup(const cv::Mat &image, const cv::Mat &lookup)
{
    cv::Mat result;
    cv::LUT(image, lookup, result);
    return result;
}


