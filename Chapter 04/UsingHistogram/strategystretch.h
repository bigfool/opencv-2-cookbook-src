#ifndef STRATEGYSTRETCH_H
#define STRATEGYSTRETCH_H

#include "processstrategy.h"
#include "strategyhistogram1d.h"

class StrategyStretch : public ProcessStrategy
{
public:
    StrategyStretch();
    virtual ~StrategyStretch();

private:
    cv::Mat ProcessAlgrithmIf(const cv::Mat &image);
    cv::Mat strech(const cv::Mat &image, int minValue = 0);
};

#endif // STRATEGYSTRETCH_H
