#ifndef CONTEXT_H
#define CONTEXT_H

#include "processstrategy.h"

class Context
{
public:
    Context(ProcessStrategy *stg);
    ~Context();

    cv::Mat doProcess(const cv::Mat &image);
private:
    ProcessStrategy *m_stg;
};

#endif // CONTEXT_H
