#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv/cxcore.h"

#include <QImage>
#include <QDateTime>
#include <QApplication>


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int count;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();



private:
    Ui::MainWindow *ui;
    QVector<QRgb> colorTable;
    CvCapture *capture;
    IplImage *pFrame;
    IplImage* iplImage;
    QImage qImage;
    QString lasttime;
    QString picname;
};

#endif // MAINWINDOW_H
