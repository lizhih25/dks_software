#include "featureextractor.h"

FeatureExtractor::FeatureExtractor(QObject *parent) :
    QObject(parent)
{
}

FeatureExtractor::FeatureExtractor(QString method, QObject *parent) :
    QObject(parent)
{
    setMethod(method);
}

bool FeatureExtractor::setMethod(QString method)
{
    /// \todo add method checker.
    mMethod = method;
    return true;
}

QString FeatureExtractor::getMethod()
{
    return mMethod;
}

bool FeatureExtractor::setRoiMat(cv::Mat roiMat)
{
    mRoiMat = roiMat.clone();
    if (mRoiMat.empty()) return false;
    else return true;
}

cv::Mat FeatureExtractor::getFeature()
{
    if (mMethod.compare("geometry") == 0) return geometryMethod(mRoiMat);
    if (mMethod.compare("compcode") == 0) return compCodeMethod(mRoiMat);
    if (mMethod.compare("ordinalcode") == 0) return ordinalCodeMethod(mRoiMat);
    if (mMethod.compare("bocv") == 0) return bocvMethod(mRoiMat);
    if (mMethod.compare("rloc") == 0) return rlocMethod(mRoiMat);
    return geometryMethod(mRoiMat); ///< defualt geemetryMethod().
}

cv::Mat FeatureExtractor::getFeature(QString method)
{
    setMethod(method);
    return getFeature();
}

cv::Mat FeatureExtractor::extractFeatureFromRoi(cv::Mat roiMat)
{
    setRoiMat(roiMat);
    return getFeature();
}

cv::Mat FeatureExtractor::extractFeatureFromRoi(cv::Mat roiMat, QString method)
{
    setRoiMat(roiMat);
    return getFeature(method);
}

cv::Mat FeatureExtractor::rlocMethod(cv::Mat inputMat)
{
    /// \todo add rloc method code
    mFeatureMat = inputMat.clone();
    qDebug() << "rloc method";
    return mFeatureMat;
}

cv::Mat FeatureExtractor::bocvMethod(cv::Mat inputMat)
{
    /// \todo add bocv method code
    mFeatureMat = inputMat.clone();
    qDebug() << "bocv method";
    return mFeatureMat;
}

cv::Mat FeatureExtractor::ordinalCodeMethod(cv::Mat inputMat)
{
    /// \todo add ordinal method code
    mFeatureMat = inputMat.clone();
    qDebug() << "ordinalCode method";
    return mFeatureMat;
}

cv::Mat FeatureExtractor::compCodeMethod(cv::Mat inputMat)
{
    /// \todo add comp method code
    mFeatureMat = inputMat.clone();
    qDebug() << "compCode method";
    return mFeatureMat;
}

cv::Mat FeatureExtractor::geometryMethod(cv::Mat inputMat)
{
    /// \todo add geometry method code
    mFeatureMat = inputMat.clone();
    qDebug() << "geometry method";
    return mFeatureMat;
}
