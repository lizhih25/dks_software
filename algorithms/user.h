#ifndef USER_H
#define USER_H

// own algorithms lib

// opencv lib
#include <opencv2/core/core.hpp>

// Qt lib
#include <QObject>
#include <QString>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = 0);
    cv::Mat image;
    QString name;
    cv::Mat roi;
    cv::Mat feature;

signals:

public slots:

};

#endif // USER_H
