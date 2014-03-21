#ifndef COLORDETECTCONTROLLER_H
#define COLORDETECTCONTROLLER_H

#include "processstrategy.h"

class ColorDetectController
{
public:
    ColorDetectController(ProcessStrategy *stg);
    ~ColorDetectController();

    void setColorDistanceThreshold(int distance);
    int getColorDistanceThreshold();
    void setTargetColor(unsigned char red, unsigned char green, unsigned char blue);
    void getTargetColor(unsigned char red, unsigned char green, unsigned char blue);

    bool setInputImage(std::string fileName);
    const cv::Mat getInputImage() const;

    void doProcess();
    const cv::Mat getLastResult() const;

    static ColorDetectController * getInstance(ProcessStrategy *stg);

private:
    ProcessStrategy *m_stg;
    cv::Mat m_image;
    cv::Mat m_result;

    //singleton
    static ColorDetectController * m_instance;
};

#endif // COLORDETECTCONTROLLER_H
