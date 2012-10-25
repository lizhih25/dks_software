#include "configure.h"

Configure::Configure(QObject *parent) :
    QObject(parent)
{
}

bool Configure::load()
{
    return load(this->mConfigFileName);
}

bool Configure::load(QString configureFileName)
{
    if (configureFileName.isNull()) return false;
    if (configureFileName.isEmpty()) return false;
    this->mConfigFileName = configureFileName;

    cv::FileStorage conf;
    if (QFile(mConfigFileName).exists()) {
        qDebug() << "There is a configure file.";
        conf.open(mConfigFileName.toAscii().data(),cv::FileStorage::READ);
        if (conf.isOpened()==false) {
            qDebug() << "Failed to open exist config file!";
            return false;
        }

        std::string tempStr;

        conf["saveRootDir"] >> tempStr;
        if (tempStr.empty()) return false;
        saveRootDir = QDir(QString::fromStdString(tempStr));
        qDebug() << saveRootDir.path();

        conf["dataSetDir"] >> tempStr;
        if (tempStr.empty()) return false;
        dataSetDir= QDir(QString::fromStdString(tempStr));

        conf.release();
        return true;
    }
    qDebug() << "There is no configure file.";
    return false;
}

bool Configure::save()
{
    return save(this->mConfigFileName);
}

bool Configure::save(QString configureFileName)
{
    if (configureFileName.isNull()) return false;
    if (configureFileName.isEmpty()) return false;
    this->mConfigFileName = configureFileName;

    if (saveRootDir.path().isNull()==true) {
        saveRootDir = QDir::currentPath();
    }

    cv::FileStorage conf(mConfigFileName.toAscii().data(), cv::FileStorage::WRITE);
    if (conf.isOpened() == false) {
        qDebug() << "Failed to open created config file!";
        return false;
    }

    conf << "saveRootDir" << saveRootDir.absolutePath().toAscii().data();
    conf << "dataSetDir" << dataSetDir.absolutePath().toAscii().data();

    conf.release();
    return true;
}


bool Configure::createDefault()
{
    mConfigFileName = QString("config.xml");
    saveRootDir = QDir::currentPath();
    dataSetDir = QDir::currentPath();

    return save();
}

bool Configure::setFileName(QString fileName)
{
    if (fileName.isNull()) return false;
    if (fileName.isEmpty()) return false;

    this->mConfigFileName = fileName;

    return true;
}
