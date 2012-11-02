#include "demo.h"

Demo::Demo(QObject *parent) :
    QObject(parent)
{
}

bool Demo::loadDataSet()
{
    return true;
}

bool Demo::saveUser(User currentUser)
{
}

bool Demo::enroll()
{
    User user;
    user.image = this->mTestMat;
    user.roi = roi_extractor.extractRoiFromImage(this->mTestMat, "kmeans");
    user.feature = feature_extractor.extractFeatureFromRoi(user.roi,"geometry");
    saveUser(user);
    this->userList.append(&user);
    return true;
}

QString Demo::identify()
{
    return "TO BE Continue\n";
}

bool Demo::verify()
{
    return true;
}

bool Demo::enroll(cv::Mat inputMat, QString name)
{
    this->mTestMat = inputMat;
    this->mTestName = name;
    return enroll();
}

QString Demo::identify(cv::Mat inputMat)
{
    this->mTestMat = inputMat;
    return identify();
}

bool Demo::verify(cv::Mat inputMat, QString name)
{
    this->mTestMat = inputMat;
    this->mTestName = name;
    return verify();
}
