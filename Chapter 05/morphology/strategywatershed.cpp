#include "strategywatershed.h"
#include <QDebug>


StrategyWatershed::StrategyWatershed()
{
    m_markers = cv::Mat();
}

StrategyWatershed::~StrategyWatershed()
{

}

void StrategyWatershed::setMarkers(const cv::Mat &markImage)
{
    markImage.convertTo(m_markers, CV_32S);
    qDebug() << "[StrategyWatershed::setMarkers]";
}

cv::Mat StrategyWatershed::getSegmentation()
{
    cv::Mat tmp;
    m_markers.convertTo(tmp, CV_8U); //CV_32S的图像不能直接显示出来，所以要转为CV_8U
    return tmp;
}

cv::Mat StrategyWatershed::getWatersheds()
{
    cv::Mat tmp;
    m_markers.convertTo(tmp, CV_8U, 255, 255);
    cv::namedWindow("Watersheds");
    cv::imshow("Watersheds", tmp);
    return tmp;
}

cv::Mat StrategyWatershed::process(const cv::Mat &image)
{
    try
    {
        cv::Mat binary;
        cv::cvtColor(image, binary, CV_BGR2GRAY); //转为灰度图

        cv::Mat fg; //前景元素
        cv::erode(binary, fg, cv::Mat(), cv::Point(-1, -1), 6); //移除噪点和微小物体

        cv::namedWindow("fg");
        cv::imshow("fg", fg);

        //识别不包含物体的像素，即背景图
        cv::Mat bg;
        cv::dilate(binary, bg, cv::Mat(), cv::Point(-1, -1), 6);
        cv::threshold(bg, bg, 1, 128, cv::THRESH_BINARY_INV);
        cv::namedWindow("bg");
        cv::imshow("bg", bg);

        //创建标记图
        cv::Mat markers(binary.size(), CV_8U, cv::Scalar(0));
        markers = fg + bg;

        cv::namedWindow("Markers");
        cv::imshow("Markers",markers);

        //设置标记，并进行处理
        setMarkers(markers);
        cv::watershed(image, m_markers); //第一个参数必须是8bit，三通道图，第二个参数必须是32位，单通道的灰度图
    }
    catch(cv::Exception e)
    {
        qDebug() << "[StrategyWatershed::process] exception: "
                 << QString::fromStdString(e.msg);
    }

    return m_markers;
}

cv::Mat StrategyWatershed::ProcessAlgrithmIf(const cv::Mat &image)
{
    process(image);
    getWatersheds();
    return getSegmentation();
}
