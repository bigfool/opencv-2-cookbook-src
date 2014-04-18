#include "controller.h"

Controller * Controller::m_instance = NULL;

Controller::Controller(ProcessStrategy *stg)
{
    m_stg = stg;
}

Controller::~Controller()
{
    if (m_stg != NULL)
    {
        delete m_stg;
        m_stg = NULL;
    }

    if (m_instance != NULL)
    {
        delete m_instance;
        m_instance = NULL;
    }
}

Controller * Controller::getInstance(ProcessStrategy *stg)
{
    if (NULL == m_instance)
    {
        m_instance = new Controller(stg);
    }

    return m_instance;
}


bool Controller::setInputImage(std::string fileName)
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

const cv::Mat Controller::getInputImage() const
{
    return m_image;
}

void Controller::doProcess()
{
    m_result = m_stg->ProcessAlgrithmIf(m_image);
}

const cv::Mat Controller::getLastResult() const
{
    return m_result;
}
