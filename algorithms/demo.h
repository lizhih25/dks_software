#ifndef DEMO_H
#define DEMO_H

// own algorithms lib
#include <../algorithms/user.h>

// opencv lib
#include <opencv2/core/core.hpp>

// Qt lib
#include <QObject>
#include <QImage>
#include <QString>
#include <QList>
#include <QLinkedList>

class Demo : public QObject
{
    Q_OBJECT
public:
    explicit Demo(QObject *parent = 0);
    bool loadData();

    bool enroll();
    QString identify();
    bool verify();

    cv::Mat testMat1,testMat2,testMat3;
    QString testName;


signals:

public slots:


private:
    QList<User*> userList;

};

#endif // DEMO_H
