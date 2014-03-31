#include <opencv2/imgproc/imgproc.hpp>
#include "strategycolorhistogram.h"

StrategyColorHistogram::StrategyColorHistogram()
{
    m_histSize[0] = m_histSize[1] = m_histSize[2] = 256;
    m_hranges[0] = 0.0;
    m_hranges[1] = 255.0;
    m_ranges[0] = m_hranges;
    m_ranges[1] = m_hranges;
    m_ranges[2] = m_hranges;
    m_channels[0] = 0;
    m_channels[1] = 1;
    m_channels[2] = 2;
}

StrategyColorHistogram::~StrategyColorHistogram()
{

}

cv::SparseMat StrategyColorHistogram::getSparseHistogram(const cv::Mat &image)
{
    cv::SparseMat hist(3, m_histSize, CV_32F);
    cv::calcHist(&image, 1, m_channels, cv::Mat(), hist, 3, m_histSize, m_ranges);
    return hist;
}

cv::MatND StrategyColorHistogram::getHistogram(const cv::Mat &image)
{
    cv::MatND hist;

    //calcHist is in opencv2/imgproc/imgproc.hpp
    cv::calcHist(&image, 1, m_channels, cv::Mat(), hist, 1, m_histSize, m_ranges);
    return hist;
}

cv::Mat StrategyColorHistogram::getHistogramImage(const cv::Mat &image, cv::Scalar color)
{
    cv::MatND hist = getHistogram(image);

    double maxVal = 0;
    double minVal = 0;
    cv::minMaxLoc(hist, &minVal, &maxVal, 0 , 0);

    cv::Mat histImg(m_histSize[0], m_histSize[0], CV_8UC3, cv::Scalar(0, 0, 0));
    int hpt = static_cast<int>(0.9 * m_histSize[0]);

    for(int h = 0; h < m_histSize[0]; h++)
    {
        float binVal = hist.at<float>(h);
        int intensity = static_cast<int>(binVal * hpt / maxVal);
        cv::line(histImg, cv::Point(h, m_histSize[0]),
                cv::Point(h, m_histSize[0] - intensity), color);
    }

    return histImg;
}

cv::Mat StrategyColorHistogram::ProcessAlgrithmIf(const cv::Mat &image)
{
    std::vector<cv::Mat> splitImages;
    cv::split(image, splitImages);

    if (splitImages.size() == 3)
    {
        cv::Mat blueImage = getHistogramImage(splitImages[0], cv::Scalar(255, 0, 0));
        cv::Mat greenImage = getHistogramImage(splitImages[1], cv::Scalar(0, 255, 0));
        cv::Mat redImage = getHistogramImage(splitImages[2], cv::Scalar(0, 0, 255));

        cv::namedWindow("blue");
        cv::imshow("blue", blueImage);

        cv::namedWindow("green");
        cv::imshow("green", greenImage);

        cv::namedWindow("red");
        cv::imshow("red", redImage);
    }

    return cv::Mat();
}
