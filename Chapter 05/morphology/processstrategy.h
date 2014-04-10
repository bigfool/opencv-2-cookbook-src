#ifndef PROCESSSTRATEGY_H
#define PROCESSSTRATEGY_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDebug>

class ProcessStrategy
{
public:
    ProcessStrategy();
    virtual ~ProcessStrategy();
    virtual cv::Mat ProcessAlgrithmIf(const cv::Mat &image) = 0;
};


#endif // PROCESSSTRATEGY_H
