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
    qDebug()  << "[ProcessStrategy::ProcessAlgrithmIf] ProcessAlgrithmIf ";
}
