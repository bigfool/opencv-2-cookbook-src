#ifndef COLORDETECTCONTROLLER_H
#define COLORDETECTCONTROLLER_H

#include "context.h"

class ColorDetectController
{
public:
    ColorDetectController();

private:
    Context *m_cont;
    cv::Mat m_image;
    cv::Mat m_result;
};

#endif // COLORDETECTCONTROLLER_H
