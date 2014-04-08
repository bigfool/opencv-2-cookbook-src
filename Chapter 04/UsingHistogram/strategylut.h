#ifndef STRATEGYLUT_H
#define STRATEGYLUT_H

#include "processstrategy.h"

class StrategyLut : public ProcessStrategy
{
public:
    StrategyLut();
    virtual ~StrategyLut();

private:
    cv::Mat ProcessAlgrithmIf(const cv::Mat &image);
    cv::Mat applyLookup(const cv::Mat &image, const cv::Mat &lookup);

private:
    cv::Mat m_lookup;
};

#endif // STRATEGYLUT_H
