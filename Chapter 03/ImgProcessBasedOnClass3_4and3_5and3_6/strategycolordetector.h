#ifndef STRATEGYCOLORDETECTOR_H
#define STRATEGYCOLORDETECTOR_H

#include "processstrategy.h"

class StrategyColorDetector : public ProcessStrategy
{
public:
    StrategyColorDetector();
    virtual ~StrategyColorDetector();

    void setColorDistanceThresholdIf(int distance) { setColorDistanceThreshold(distance);}
    int getColorDistanceThresholdIf() { return getColorDistanceThreshold(); }

    void setTargetColorIf(unsigned char red, unsigned char green, unsigned char blue);
    void getTargetColorIf(unsigned char &red, unsigned char &green, unsigned char &blue);

private:
    void setColorDistanceThreshold(int distance);
    int getColorDistanceThreshold() const;

    // Sets the color to be detected
    void setTargetColor(unsigned char red, unsigned char green, unsigned char blue);
    void setTargetColor(cv::Vec3b color);
    cv::Vec3b getTargetColor() const;

    cv::Mat ProcessAlgrithmIf(const cv::Mat &image);

    int getDistance(const cv::Vec3b &color) const;

private:
    int m_minDist;
    cv::Vec3b m_target;
    cv::Mat m_result;
    cv::Mat m_converted;

};

#endif // STRATEGYCOLORDETECTOR_H
