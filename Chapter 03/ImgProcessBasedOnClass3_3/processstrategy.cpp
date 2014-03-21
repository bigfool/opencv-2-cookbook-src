#include "processstrategy.h"

ProcessStrategy::ProcessStrategy()
{
}

ProcessStrategy::~ProcessStrategy()
{
    qDebug() << "[ProcessStrategy::~ProcessStrategy] ~ProcessStrategy";
}

cv::Mat ProcessStrategy::ProcessAlgrithmIf(const cv::Mat &image)
{
    qDebug() << "[ProcessStrategy::ProcessAlgrithmIf] ProcessAlgrithmIf ";
}

void ProcessStrategy::setColorDistanceThresholdIf(int distance)
{
    qDebug() << "[ProcessStrategy::setColorDistanceThreshold] distance = " << distance;
}

int ProcessStrategy::getColorDistanceThresholdIf()
{
    qDebug() << "[ProcessStrategy::getColorDistanceThreshold]";
    return 0;
}

void ProcessStrategy::setTargetColorIf(unsigned char red, unsigned char green, unsigned char blue)
{
    qDebug() << QString("[ProcessStrategy::setTargetColor]red = %1 green = %2 blue = %3").arg(red).arg(green).arg(blue);
}

void ProcessStrategy::getTargetColorIf(unsigned char &red, unsigned char &green, unsigned char &blue)
{
    qDebug() << "[ProcessStrategy::getTargetColor]";
}

