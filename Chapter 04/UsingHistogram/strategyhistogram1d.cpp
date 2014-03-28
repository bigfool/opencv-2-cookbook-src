#include "strategyhistogram1d.h"
#include <opencv2/imgproc/imgproc.hpp>

StrategyHistogram1D::StrategyHistogram1D()
{
    m_histSize[0] = 256;
    m_hranges[0] = 0.0;
    m_hranges[1] = 255.0;
    m_ranges[0] = m_hranges;
    m_channels[0] = 0;
}

StrategyHistogram1D::~StrategyHistogram1D()
{

}

cv::MatND StrategyHistogram1D::getHistogram(const cv::Mat &image)
{
    cv::MatND hist;

    //calcHist is in opencv2/imgproc/imgproc.hpp
    cv::calcHist(&image, 1, m_channels, cv::Mat(), hist, 1, m_histSize, m_ranges);
    return hist;
}

cv::Mat StrategyHistogram1D::getHistogramImage(const cv::Mat &image)
{
    cv::MatND hist = getHistogram(image);

    double maxVal = 0;
    double minVal = 0;
    cv::minMaxLoc(hist, &minVal, &maxVal, 0 , 0);

    cv::Mat histImg(m_histSize[0], m_histSize[0], CV_8U, cv::Scalar(255));
    int hpt = static_cast<int>(0.9 * m_histSize[0]);

    for(int h = 0; h < m_histSize[0]; h++)
    {
        float binVal = hist.at<float>(h);
        int intensity = static_cast<int>(binVal * hpt / maxVal);
        cv::line(histImg, cv::Point(h, m_histSize[0]),
                cv::Point(h, m_histSize[0] - intensity), cv::Scalar::all(0));
    }

    cv::namedWindow("histogram");
    cv::imshow("histogram", histImg);

    cv::Mat threshoded;
    cv::threshold(image, threshoded, 70, 255, cv::THRESH_BINARY);

    cv::namedWindow("binary image");
    cv::imshow("binary image", threshoded);

    return histImg;
}

cv::Mat StrategyHistogram1D::ProcessAlgrithmIf(const cv::Mat &image)
{
    return getHistogramImage(image);
}
