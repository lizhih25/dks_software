#include "roiextractor.h"

RoiExtractor::RoiExtractor(QObject *parent) :
    QObject(parent)
{
}


RoiExtractor::RoiExtractor(QString method, QObject *parent) :
    QObject(parent)
{
    setMethod(method);
}

bool RoiExtractor::setMethod(QString method)
{
    /// \todo add method checker.
    mMethod = method;
    return true;
}

QString RoiExtractor::getMethod()
{
    return mMethod;
}


bool RoiExtractor::setSrcMat(cv::Mat inputMat)
{
    mSrcMat = inputMat.clone();
    if (mSrcMat.empty()) return false;
    else return true;
}

cv::Mat RoiExtractor::getRoi()
{
    if (mMethod.compare("geometry") == 0) return geometryMethod(mSrcMat);
    if (mMethod.compare("kmeans") == 0) return kmeansMethod(mSrcMat);
    return geometryMethod(mSrcMat); ///< defualt geemetryMethod().
}

cv::Mat RoiExtractor::getRoi(QString method)
{
    setMethod(method);
    return getRoi();
}

cv::Mat RoiExtractor::extractRoiFromImage(cv::Mat inputMat)
{
    setSrcMat(inputMat);
    return getRoi();
}

cv::Mat RoiExtractor::extractRoiFromImage(cv::Mat inputMat, QString method)
{
    setSrcMat(inputMat);
    return getRoi(method);
}

cv::Mat RoiExtractor::kmeansMethod(cv::Mat inputMat)
{
    /// \todo add kmeans method code
    mRoiMat = inputMat.clone();
    qDebug() << "K-means method";
    return mRoiMat;
}

cv::Mat RoiExtractor::geometryMethod(cv::Mat inputMat)
{
    /// \todo add geometry method code
    mRoiMat = inputMat.clone();
    qDebug() << "geometry method";
    return mRoiMat;
}

