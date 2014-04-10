#ifndef STRATEGYMORPHOLINE_H
#define STRATEGYMORPHOLINE_H

#include "processstrategy.h"
#include <opencv2/imgproc/imgproc.hpp>

class StrategyMorphoLine : public ProcessStrategy
{
public:
    StrategyMorphoLine();
    virtual ~StrategyMorphoLine();

    void setThreshold(int value) { m_threshold = value; }
    int getThreshold() { return m_threshold; }

private:
    cv::Mat ProcessAlgrithmIf(const cv::Mat &image);
    cv::Mat getEdges(const cv::Mat &image);
    void applyThreshold(cv::Mat &result);

private:
    int m_threshold;//用于生成二值图像的阈值
};

#endif // STRATEGYMORPHOLINE_H
