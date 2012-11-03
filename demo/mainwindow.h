#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// own algorithms lib
#include <../algorithms/fovmarker.h>
#include <../algorithms/configure.h>
#include <../algorithms/demo.h>

// opencv lib
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Qt lib
#include <QMainWindow>
#include <QImage>
#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QShortcut>
#include <QFileDialog>


// class naming conventions
// m for members
// c for constants/readonlys
// p for pointer (and pp for pointer to pointer)
// v for volatile
// s for static
// i for indexes and iterators
// e for events


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);

private slots:

    void change_camera(int camid = 0);
    void change_camera_0();
    void change_camera_1();
    void change_camera_2();
    void change_configure();
    void change_rootDir();


    void on_registerPushButton_clicked();

    void on_userNameLineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    Demo demo;
    QString mTestName;

    cv::VideoCapture mShowingCapture;
    cv::Mat mCapturedMat;
    cv::Mat mTempMat;

    FovMarker mFovMarker;

    QImage mDisplayImage;

    Configure cfg;
};

#endif // MAINWINDOW_H
