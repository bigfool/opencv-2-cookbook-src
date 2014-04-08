#ifndef STRATEGYEQUALIZE_H
#define STRATEGYEQUALIZE_H

#include "processstrategy.h"

class StrategyEqualize : public ProcessStrategy
{
public:
    StrategyEqualize();
    virtual ~StrategyEqualize();

private:
    cv::Mat ProcessAlgrithmIf(const cv::Mat &image);
    cv::Mat equalize(const cv::Mat &image);
};

#endif // STRATEGYEQUALIZE_H
