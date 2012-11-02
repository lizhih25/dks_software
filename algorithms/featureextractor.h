#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#include <opencv2/core/core.hpp>

#include <QObject>
#include <QDebug>

class FeatureExtractor : public QObject
{
    Q_OBJECT
public:
    explicit FeatureExtractor(QObject *parent = 0);

    FeatureExtractor(QString method, QObject *parent = 0);
    bool setMethod(QString method);
    QString getMethod();
    bool setRoiMat(cv::Mat roiMat);
    cv::Mat getFeature();
    cv::Mat getFeature(QString method);
    cv::Mat extractFeatureFromRoi(cv::Mat roiMat);
    cv::Mat extractFeatureFromRoi(cv::Mat roiMat, QString method);


signals:

public slots:

private:
    QString mMethod;
    cv::Mat mRoiMat;
    cv::Mat mFeatureMat;

    cv::Mat geometryMethod(cv::Mat inputMat);
    cv::Mat compCodeMethod(cv::Mat inputMat);
    cv::Mat ordinalCodeMethod(cv::Mat inputMat);
    cv::Mat bocvMethod(cv::Mat inputMat);
    cv::Mat rlocMethod(cv::Mat inputMat);


};

#endif // FEATUREEXTRACTOR_H
