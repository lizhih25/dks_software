#ifndef ROCEXTRACTOR_H
#define ROCEXTRACTOR_H

#include <QObject>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


class RocExtractor : public QObject
{
    Q_OBJECT
public:
    explicit RocExtractor(QObject *parent = 0);
    void setSrcImage(const cv::Mat& im);
    cv::Mat getRocImage();

    cv::Point2d center;
    double innerRadius;
    double outerRadius;
    //    +--------------------------------------------+
    //    |                 ,,.----.,,                 |
    //    |             ,-``          ``',,            |
    //    |          ,-`                   ',          |
    //    |         -      innerRatius       ',        |
    //    |       ,'         _,.--.,,          \       |
    //    |      /         .`        .',        \      |
    //    |     /        ,'        ,'   .       \      |
    //    |     |       / center  -      ,       |     |
    //    |     |       |       @`----------------     |
    //    |     |       \   outerRadius  '       |     |
    //    |      ,       `,             `       /      |
    //    |      \         ',        ,-`        /      |
    //    |       `.         `''--''`          /       |
    //    |         .                        .`        |
    //    |          `.,                   .`          |
    //    |             '-,_          _,-'`            |
    //    |                 `'''---''`                 |
    //    +--------------------------------------------+
    double verticalDis;
    double height;
    double width;
    //    |                                                   |
    //    |                         @ image center            |
    //    |                         |                         |
    //    |                         |  verticalDis            |
    //    |                         |                         |
    //    |             upleft @----+-----+                   |
    //    |                    |          |                   |
    //    |                    |          |  height           |
    //    |                    |          |                   |
    //    |                    +----------@ downright         |
    //    |                        width                      |
    //    |                                                   |
    //    |                                                   |
    //    +---------------------------------------------------+

private:
    cv::Mat srcImage;
    cv::Mat rocImage;
    void run();
    bool debug;
    cv::Mat drawFov(cv::Mat& im);
    cv::Mat drawReferRegion(cv::Mat& im);

signals:

public slots:

};

#endif // ROCEXTRACTOR_H
