#ifndef USER_H
#define USER_H

// own algorithms lib

// opencv lib
#include <opencv2/core/core.hpp>

// Qt lib
#include <QString>

class User
{
public:
    User();
    cv::Mat image;
    QString name;
    cv::Mat roi;
    cv::Mat feature;

};

#endif // USER_H
