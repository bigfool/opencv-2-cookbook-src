#ifndef STRATEGYCONTENTFINDER_H
#define STRATEGYCONTENTFINDER_H

#include "processstrategy.h"
#include "strategycolorhistogram.h"

class StrategyContentFinder : public ProcessStrategy
{
public:
    StrategyContentFinder();
    virtual ~StrategyContentFinder();

    void serThreshold(float t) { m_threshold = t; }
    float getThreshold() { return m_threshold; }

    void setHistogram(const cv::MatND &h);

private:
    cv::Mat colorReduce(cv::Mat &img, int div);
    cv::Mat ProcessAlgrithmIf(const cv::Mat &image);
//    cv::Mat find(const cv::Mat &image, float minValue, float maxValue, int *channels, int dim);
    cv::Mat find(const cv::Mat &image, float minValue, float maxValue);

private:
    float m_hranges[2];
    const float *m_ranges[3];
    int m_channels[3];
    float m_threshold;
    cv::MatND m_histogram;
};

#endif // STRATEGYCONTENTFINDER_H
