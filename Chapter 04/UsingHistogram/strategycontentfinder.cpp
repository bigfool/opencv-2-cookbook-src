#include "strategycontentfinder.h"
#include <opencv2/imgproc/imgproc.hpp>

StrategyContentFinder::StrategyContentFinder()
{
    m_threshold = -1.0;
    m_ranges[0] = m_hranges;
    m_ranges[1] = m_hranges;
    m_ranges[2] = m_hranges;

    m_channels[0] = 0;
    m_channels[1] = 1;
    m_channels[2] = 2;
}

StrategyContentFinder::~StrategyContentFinder()
{

}

void StrategyContentFinder::setHistogram(const cv::MatND &h)
{
    m_histogram = h;
    cv::normalize(m_histogram, m_histogram, 1.0);
}

cv::Mat StrategyContentFinder::colorReduce(cv::Mat &img, int div)
{
    cv::Mat image;
    img.copyTo(image);
    int nl = image.rows; //rows
    int nc = image.cols * image.channels();

    if (image.isContinuous())
    {
        nc = nc * nl;
        nl = 1;
    }

    for (int j = 0; j < nl; j++)
    {
        uchar *data = image.ptr<uchar>(j);
        for (int i = 0; i < nc; i++)
        {
//            data[i] = data[i] / div * div + div / 2;

            // for speed
            uchar mask = 0xFF << div;
            data[i] = (data[i] & mask) + div / 2;
        }

        //or
//        *data++ = *data / div * div + div / 2;
    }

    return image;
}

//cv::Mat StrategyContentFinder::find(const cv::Mat &image,
//                                    float minValue, float maxValue, int *channels, int dim)
cv::Mat StrategyContentFinder::find(const cv::Mat &image,
                                    float minValue, float maxValue)
{
    cv::Mat result;
    m_hranges[0] = minValue;
    m_hranges[1] = maxValue;

//    for (int i = 0; i < dim; i++)
//    {
//        this->m_channels[i] = channels[i];
//    }

    cv::calcBackProject(&image,       //输入图片
                        1,            //一张图片
                        m_channels,     //所用通道列表
                        m_histogram,  //直方图
                        result,       //反投影的结果
                        m_ranges,     //值域
                        255.0);       //缩放因子

    //进行阈值化以得到二值图像
    if (m_threshold > 0.0)
    {
        cv::threshold(result, result, 255 * m_threshold, 255, cv::THRESH_BINARY);
    }

    return result;
}

cv::Mat StrategyContentFinder::ProcessAlgrithmIf(const cv::Mat &image)
{
    cv::Mat color;
    image.copyTo(color);
    color = colorReduce(color, 32);

    cv::Mat imageROI = color(cv::Rect(0, 0, 165, 75));

    StrategyColorHistogram hc;
    cv::MatND hist = hc.getHistogram(imageROI);

    setHistogram(hist);
    serThreshold(0.05f);

    cv::Mat result = find(color,150, 200);

    return result;
}
