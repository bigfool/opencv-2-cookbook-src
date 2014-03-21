#include "colordetectcontroller.h"

ColorDetectController::ColorDetectController(ProcessStrategy *stg)
{
    m_stg = stg;
}

ColorDetectController::~ColorDetectController()
{
    if (m_stg != NULL)
    {
        delete m_stg;
        m_stg = NULL;
    }
}

void ColorDetectController::setColorDistanceThreshold(int distance)
{
    m_stg->setColorDistanceThresholdIf(distance);
}

int ColorDetectController::getColorDistanceThreshold()
{
    return m_stg->getColorDistanceThresholdIf();
}

void ColorDetectController::setTargetColor(unsigned char red, unsigned char green, unsigned char blue)
{
    m_stg->setTargetColorIf(red, green, blue);
}

void ColorDetectController::getTargetColor(unsigned char red, unsigned char green, unsigned char blue)
{
    m_stg->getTargetColorIf(red, green, blue);
}

bool ColorDetectController::setInputImage(std::string fileName)
{
    m_image = cv::imread(fileName);
    if (!m_image.data)
    {
        qDebug() << "[ColorDetectController::setInputImage] can't open image";
        return false;
    }
    else
    {
        return true;
    }
}

const cv::Mat ColorDetectController::getInputImage() const
{
    return m_image;
}

void ColorDetectController::doProcess()
{
    m_result = m_stg->ProcessAlgrithmIf(m_image);
}

const cv::Mat ColorDetectController::getLastResult() const
{
    return m_result;
}
