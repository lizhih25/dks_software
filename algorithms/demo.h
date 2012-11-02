#ifndef DEMO_H
#define DEMO_H

// own algorithms lib
#include <../algorithms/user.h>
#include <../algorithms/roiextractor.h>
#include <../algorithms/featureextractor.h>

// opencv lib
#include <opencv2/core/core.hpp>

// Qt lib
#include <QObject>
#include <QImage>
#include <QString>
#include <QList>
#include <QLinkedList>
#include <QDir>

class Demo : public QObject
{
    Q_OBJECT
public:
    explicit Demo(QObject *parent = 0);
    bool setDataSet(QDir dataSetDir);

    bool enroll();
    bool enroll(cv::Mat inputMat, QString name);
    QString identify();
    QString identify(cv::Mat inputMat);
    bool verify();
    bool verify(cv::Mat inputMat, QString name);

    /// generallly enroll user should provide one image,
    /// but sometime there should be more images.
    cv::Mat mTestMat;

    QString mTestName;

signals:

public slots:


private:
    RoiExtractor roi_extractor;
    FeatureExtractor feature_extractor;

    QDir mDataSetDir;
    QList<User*> userList;

    bool loadDataSet();

    bool saveUser(User currentUser);
    User loadUser(QString userName);
};

#endif // DEMO_H
