#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "processstrategy.h"

class Controller
{
public:
    Controller(ProcessStrategy *stg);
    ~Controller();

    bool setInputImage(std::string fileName);
    const cv::Mat getInputImage() const;

    void doProcess();
    const cv::Mat getLastResult() const;

    static Controller * getInstance(ProcessStrategy *stg);

private:
    static Controller * m_instance;
    ProcessStrategy *m_stg;
    cv::Mat m_image;
    cv::Mat m_result;
};

#endif // CONTROLLER_H
