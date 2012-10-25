/////////////////////////////////////////////////////////
/// \brief Mark the fov of the door knob system
///
/// The Field of View(FOV) means the ring area, especially
/// the referenc rectangle area between the two pegs. Mark
/// these areas to calibrate the device and make sure the
/// image quality is good enough.
///
/////////////////////////////////////////////////////////

#ifndef FOVMARKER_H
#define FOVMARKER_H

// own algorithms lib

// opencv lib
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// Qt lib
#include <QObject>

/// Draw markers on the image
class FovMarker : public QObject
{
    Q_OBJECT

public:
    explicit FovMarker(QObject *parent = 0);///< init parameter
    void setSrcImage(const cv::Mat& im);///< save a clone of the src image
    cv::Mat getMarkedImage();///< get a image marked with current parameters
    ///< return null image if the src image is not set

    cv::Point2d center;///< The center of the two circles. Percentage to image size
    double innerRadius;///< Percentage to image width
    double outerRadius;/// Percentage to image width

    double verticalDis;///< percentage to image height
    double height;///< height of ref region, percentage to image height
    double width;///< width of ref region,  percentage to image width

private:
    cv::Mat srcImage;
    cv::Mat markedImage;

    bool isDebuging;

    ///< draw the field of view including two circles and the center
    cv::Mat drawFov(cv::Mat& im);
    /// draw the reference region between two pegs
    cv::Mat drawReferRegion(cv::Mat& im);

signals:

public slots:

};

#endif // FOVMARKER_H
