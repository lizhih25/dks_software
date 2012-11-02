#ifndef ROIEXTRACTOR_H
#define ROIEXTRACTOR_H

// algo

// opencv
#include <opencv2/core/core.hpp>

// qt
#include <QObject>
#include <QDebug>
#include <QString>

class RoiExtractor : public QObject
{
    Q_OBJECT
public:
    explicit RoiExtractor(QObject *parent = 0);
    RoiExtractor(QString method, QObject *parent = 0);
    bool setMethod(QString method);
    QString getMethod();
    bool setSrcMat(cv::Mat inputMat);
    cv::Mat getRoi();
    cv::Mat getRoi(QString method);
    cv::Mat extractRoiFromImage(cv::Mat inputMat);
    cv::Mat extractRoiFromImage(cv::Mat inputMat, QString method);


signals:

public slots:

private:
    QString mMethod;
    cv::Mat mSrcMat;
    cv::Mat mRoiMat;

    cv::Mat geometryMethod(cv::Mat inputMat);
    cv::Mat kmeansMethod(cv::Mat inputMat);

};

#endif // ROIEXTRACTOR_H
