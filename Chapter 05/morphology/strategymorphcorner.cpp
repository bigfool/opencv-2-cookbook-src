#include "strategymorphcorner.h"


/* 在形态学上前景色用白色（1），背景色用黑色（0） */
StrategyMorphCorner::StrategyMorphCorner()
    : m_threshold(-1), m_cross(5, 5, CV_8U, cv::Scalar(0)),
      m_diamond(5, 5, CV_8U, cv::Scalar(1)), m_square(5, 5, CV_8U, cv::Scalar(1)),
      m_x(5, 5, CV_8U, cv::Scalar(0))
{
    //创建十字形元素
    for(int i = 0; i < 5; i++)
    {
        m_cross.at<uchar>(2, i) = 1;
        m_cross.at<uchar>(i, 2) = 1;
    }

    //创建菱形元素
    m_diamond.at<uchar>(0, 0) = 0; //左上角像素
    m_diamond.at<uchar>(0, 1) = 0; //左上角像素
    m_diamond.at<uchar>(1, 0) = 0; //左上角像素

    m_diamond.at<uchar>(4, 4) = 0; //右下角像素
    m_diamond.at<uchar>(3, 4) = 0; //右下角像素
    m_diamond.at<uchar>(4, 4) = 0; //右下角像素

    m_diamond.at<uchar>(4, 0) = 0; //左下角像素
    m_diamond.at<uchar>(4, 1) = 0; //左下角像素
    m_diamond.at<uchar>(3, 0) = 0; //左下角像素

    m_diamond.at<uchar>(0, 4) = 0; //右上角像素
    m_diamond.at<uchar>(0, 3) = 0; //右上角像素
    m_diamond.at<uchar>(1, 4) = 0; //右上角像素

    //创建X形元素
    for (int i = 0; i < 5; i++)
    {
        m_x.at<uchar>(i, i) = 1;
        m_x.at<uchar>(4-i, i) = 1;
    }
}

StrategyMorphCorner::~StrategyMorphCorner()
{

}

void StrategyMorphCorner::applyThreshold(cv::Mat &result)
{
    if (m_threshold > 0)
    {
        cv::threshold(result, result, m_threshold, 255, cv::THRESH_BINARY);
    }
    else
    {
        qDebug() << "[StrategyMorphCorner::applyThreshold] threshold value < 0";
    }
}

cv::Mat StrategyMorphCorner::getCornors(const cv::Mat &image)
{
     qDebug() << "[StrategyMorphCorner::getCornors] start ";
    cv::Mat result;
    try
    {
        cv::dilate(image, result, m_cross);     //十字形膨胀
        cv::erode(result, result, m_diamond);   //菱形腐蚀

        cv::Mat result2;
        cv::dilate(image, result2, m_x);        //X形膨胀
        cv::erode(result2, result2, m_square);  //方形腐蚀

        cv::absdiff(result2, result, result); //通过两张图像做差值得到角点图像
    }
    catch(cv::Exception e)
    {
        qDebug() << "[StrategyMorphCorner::getCornors] exception: "
                 << QString::fromStdString(e.msg);
    }

    applyThreshold(result); //阈值化以得到二值图像
    qDebug() << "[StrategyMorphCorner::getCornors] over ";

    return result;
}

void StrategyMorphCorner::drawOnImage(const cv::Mat &binary, cv::Mat &image)
{
    qDebug() << "[StrategyMorphCorner::drawOnImage] start ";
    cv::Mat_<uchar>::const_iterator it = binary.begin<uchar>();
    cv::Mat_<uchar>::const_iterator itend = binary.end<uchar>();

//    try
//    {
        for(int i = 0; it != itend; ++it, ++i)
        {
            if (!*it)
            {
                cv::circle(image, cv::Point(i%image.step, i/image.step),
                           5, cv::Scalar(255, 0, 0));
            }
        }
//    }
//    catch (cv::Exception e)
//    {
//        qDebug() << "[StrategyMorphCorner::drawOnImage] exception: "
//                 << QString::fromStdString(e.msg);
//    }
     qDebug() << "[StrategyMorphCorner::drawOnImage] over ";
}

cv::Mat StrategyMorphCorner::ProcessAlgrithmIf(const cv::Mat &image)
{
    qDebug() << "[StrategyMorphCorner::ProcessAlgrithmIf] start ";
    cv::Mat corners;
    cv::Mat result = image.clone();

    cv::namedWindow("result");
    cv::imshow("result",result);

    corners = getCornors(image);

    cv::namedWindow("corner");
    cv::imshow("corner",corners);

    drawOnImage(corners, result);
    qDebug() << "[StrategyMorphCorner::ProcessAlgrithmIf] over ";

//    cv::imshow("corner",result);

    return result;
}

