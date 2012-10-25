#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// own algorithms lib
#include <../algorithms/fovmarker.h>
#include <../algorithms/configure.h>
#include <../algorithms/anyoption.h>

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
    void optionAndConfigParse(int argc, char* argv[]);

private slots:
    void on_imagebutton_clicked();

    void on_videobutton_clicked();

    void change_camera(int camid = 0);
    void change_camera_0();
    void change_camera_1();
    void change_camera_2();
    void change_configure();
    void change_rootDir();

    void on_userHandComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    Configure cfg;
    static const QString scImageDir;
    static const QString scVideoDir;
    QString mUserHand;
    QDir mVideoDir;

    int miImage;
    int miVideoFrame;

    cv::VideoCapture mShowingCapture;
    cv::Mat mCapturedMat;
    cv::Mat mTempMat;
    cv::VideoWriter mRecordVideo;

    FovMarker mFovMarker;

    QImage mDisplayImage;
    QString mLastTimeString;

    static const int scReordTimeLength = 5;
    static const int scRecordFps = 20;

};

#endif // MAINWINDOW_H
