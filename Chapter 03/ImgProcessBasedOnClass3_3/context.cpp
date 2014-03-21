#include "context.h"

Context::Context(ProcessStrategy *stg)
{
    m_stg = stg;
}

Context::~Context()
{
    if (m_stg != NULL)
    {
        delete m_stg;
    }
}

cv::Mat Context::doProcess(const cv::Mat &image)
{
    return m_stg->ProcessAlgrithmIf(image);
}
