#ifndef PROCESSSTRATEGY_H
#define PROCESSSTRATEGY_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDebug>

// strategy class
class ProcessStrategy
{
public:
    ProcessStrategy();
    virtual ~ProcessStrategy();
    virtual cv::Mat ProcessAlgrithmIf(const cv::Mat &image) = 0;
    virtual void setColorDistanceThresholdIf(int distance) = 0;
    virtual int getColorDistanceThresholdIf() = 0;
    virtual void setTargetColorIf(unsigned char red, unsigned char green, unsigned char blue) = 0;
    virtual void getTargetColorIf(unsigned char &red, unsigned char &green, unsigned char &blue) = 0;
};

#endif // PROCESSSTRATEGY_H
