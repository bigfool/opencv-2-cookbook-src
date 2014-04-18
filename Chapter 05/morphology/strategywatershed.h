#ifndef STRATEGYWATERSHED_H
#define STRATEGYWATERSHED_H

#include "processstrategy.h"
#include <opencv2/imgproc/imgproc.hpp>

class StrategyWatershed : public ProcessStrategy
{
public:
    StrategyWatershed();
    virtual ~StrategyWatershed();

    void setMarkers(const cv::Mat & markImage);

    cv::Mat getSegmentation();
    cv::Mat getWatersheds();

private:
    cv::Mat ProcessAlgrithmIf(const cv::Mat &image);
    cv::Mat process(const cv::Mat &image);

private:
    cv::Mat m_markers;
};

#endif // STRATEGYWATERSHED_H
