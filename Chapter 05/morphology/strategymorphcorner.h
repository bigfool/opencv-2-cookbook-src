#ifndef STRATEGYMORPHCORNER_H
#define STRATEGYMORPHCORNER_H

#include "processstrategy.h"

#include <opencv2/imgproc/imgproc.hpp>

class StrategyMorphCorner : public ProcessStrategy
{
public:
    StrategyMorphCorner();
    virtual ~StrategyMorphCorner();

    int getThreshold() { return m_threshold; }
    void setThreshold(int value) { m_threshold = value; }

private:
    cv::Mat ProcessAlgrithmIf(const cv::Mat &image);
    cv::Mat getCornors(const cv::Mat &image);
    void applyThreshold(cv::Mat &result);
    void drawOnImage(const cv::Mat &binary, cv::Mat &image);

private:
    int m_threshold;
    // 角点检测中用到的结构元素
    cv::Mat m_cross;    //十字形结构元素
    cv::Mat m_diamond;  //菱形结构元素
    cv::Mat m_square;   //方形
    cv::Mat m_x;        //X形
};

#endif // STRATEGYMORPHCORNER_H
