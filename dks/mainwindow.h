#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/// own algorithms lib
#include <../algorithms/rocextractor.h>

/// opencv lib
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/// Qt lib
#include <QMainWindow>
#include <QImage>
#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QShortcut>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int imagecount;
    int videocount;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);

private slots:
    void on_imagebutton_clicked();

    void on_videobutton_clicked();

    void change_camera(int camid = 0);
    void change_camera_0();
    void change_camera_1();
    void change_camera_2();

private:
    Ui::MainWindow *ui;

    cv::VideoCapture showingCapture;
    cv::Mat capturedMat;
    cv::Mat tempMat;
    cv::VideoWriter recordVideo;

    RocExtractor rocExtractor;

    QImage displayImage;
    QString lasttime;
    QString picname;

    const static int TIME = 5;
    const static int FPS = 20;
};

#endif // MAINWINDOW_H
