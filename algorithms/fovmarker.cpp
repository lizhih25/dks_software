#include "fovmarker.h"

FovMarker::FovMarker(QObject *parent) :
    QObject(parent)
{
    isDebuging = true;
    center = cv::Point2d(0.46875f,0.477f);
    innerRadius = 0.1421875f;
    outerRadius = 0.3828125f;
    verticalDis = 0.22f;
    height = 0.23542f;
    width = 0.259375f;
}


void FovMarker::setSrcImage(const cv::Mat &im)
{
    this->srcImage = im.clone();
}

cv::Mat FovMarker::getMarkedImage()
{
    if (this->srcImage.data){
        markedImage = drawReferRegion(drawFov(srcImage.clone()));
    }
    return this->markedImage;
}

cv::Mat FovMarker::drawFov(cv::Mat& im)
{
    ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///    +--------------------------------------------+
    ///    |                 ,,.----.,,                 |
    ///    |             ,-``          ``',,            |
    ///    |          ,-`                   ',          |
    ///    |         -      innerRatius       ',        |
    ///    |       ,'         _,.--.,,          \       |
    ///    |      /         .`        .',        \      |
    ///    |     /        ,'        ,'   .       \      |
    ///    |     |       / center  -      ,       |     |
    ///    |     |       |       @`----------------     |
    ///    |     |       \   outerRadius  '       |     |
    ///    |      ,       `,             `       /      |
    ///    |      \         ',        ,-`        /      |
    ///    |       `.         `''--''`          /       |
    ///    |         .                        .`        |
    ///    |          `.,                   .`          |
    ///    |             '-,_          _,-'`            |
    ///    |                 `'''---''`                 |
    ///    +--------------------------------------------+
    ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (im.channels() == 1) cv::cvtColor(im,im,CV_GRAY2BGR);
    int thickness(2);
    cv::Scalar fillColor(0,0,255);
    cv::Point2d centerPoint(center.x * im.cols, center.y * im.rows);
    cv::circle(im, centerPoint, thickness, fillColor, thickness, 8, 0);
    cv::circle(im, centerPoint, innerRadius*im.cols, fillColor, thickness, 8, 0);
    cv::circle(im, centerPoint, outerRadius*im.cols, fillColor, thickness, 8, 0);
    return im;
}


cv::Mat FovMarker::drawReferRegion(cv::Mat& im)
{
    ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///    |                                                   |
    ///    |                         @ image center            |
    ///    |                         |                         |
    ///    |                         |  verticalDis            |
    ///    |                         |                         |
    ///    |             upleft @----+-----+                   |
    ///    |                    |          |                   |
    ///    |                    |          |  height           |
    ///    |                    |          |                   |
    ///    |                    +----------@ downright         |
    ///    |                        width                      |
    ///    |                                                   |
    ///    |                                                   |
    ///    +---------------------------------------------------+
    ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cv::Point2d upleft(center.x * im.cols - width / 2.0f * im.cols,
                       center.y * im.rows + verticalDis  * im.rows);
    cv::Point2d downright(upleft.x + width  * im.cols,
                          upleft.y + height * im.rows);
    if (im.channels() == 1) cv::cvtColor(im,im,CV_GRAY2BGR);
    int thickness(1);
    cv::Scalar fillColor(0,255,0);
    cv::rectangle(im, upleft, downright, fillColor, thickness,8);
    return im;
}



