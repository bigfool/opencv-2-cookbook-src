#ifndef STRATEGYCOLORHISTOGRAM_H
#define STRATEGYCOLORHISTOGRAM_H

#include "processstrategy.h"

class StrategyColorHistogram : public ProcessStrategy
{
public:
    StrategyColorHistogram();
    virtual ~StrategyColorHistogram();

private:
    cv::Mat ProcessAlgrithmIf(const cv::Mat &image);
    cv::SparseMat getSparseHistogram(const cv::Mat &image);
    cv::Mat getHistogram(const cv::Mat &image);
    cv::Mat getHistogramImage(const cv::Mat &image);

private:
    int m_histSize[3];
    float m_hranges[2];
    const float * m_ranges[3];
    int m_channels[3];
};

#endif // STRATEGYCOLORHISTOGRAM_H
