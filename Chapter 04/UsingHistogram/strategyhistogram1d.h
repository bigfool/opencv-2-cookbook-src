#ifndef STRATEGYHISTOGRAM1D_H
#define STRATEGYHISTOGRAM1D_H

#include "processstrategy.h"

class StrategyHistogram1D : public ProcessStrategy
{
public:
    StrategyHistogram1D();
    virtual ~StrategyHistogram1D();
    cv::MatND getHistogram(const cv::Mat &image);
    int getHistSize() { return m_histSize[0]; }
    cv::Mat getHistogramImage(const cv::Mat &image);

private:
    cv::Mat ProcessAlgrithmIf(const cv::Mat &image);


private:
    int m_histSize[1];
    float m_hranges[2];
    const float *m_ranges[1];
    int m_channels[1];
};

#endif // STRATEGYHISTOGRAM1D_H
