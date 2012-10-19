#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :    QMainWindow(parent),    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        count=1;
    for(int i=0; i<=0xFF; i++){
        colorTable.push_back(qRgb(i,i,i));
    }

    capture=cvCaptureFromCAM(2);    //设置摄像头
}

MainWindow::~MainWindow()
{
    cvReleaseCapture(&capture);
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *)
{
    if(capture)
    {
        pFrame=cvQueryFrame(capture);
        CvSize dst_size;        //设置图片大小
        dst_size.height=480;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            ;
        dst_size.width=640;
        iplImage=cvCreateImage(dst_size,8,3);
        cvResize(pFrame,iplImage,CV_INTER_AREA);//图像适应大小
        cvCvtColor(iplImage,iplImage,CV_BGR2RGB);
        qImage=QImage((unsigned char *)iplImage->imageDataOrigin,iplImage->width,iplImage->height,QImage::Format_RGB888);
        cvReleaseImage( &iplImage );
        ui->labelVideo->setPixmap(QPixmap::fromImage(qImage));
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString userName=ui->userNameLineEdit->text();
    QString userHand=ui->userHandComboBox->currentText();
    QDir *tempDir = new QDir;
    bool exist = tempDir->exists(userName);     //判断目录是否存在，不存在便新建
    if(!exist)
    {
        tempDir->mkdir(userName);
        QString tempStr1 = userName + "/L";
        QString tempStr2 = userName + "/R";
        tempDir->mkdir(tempStr1);
        tempDir->mkdir(tempStr2);
    }

    QDateTime datetime=QDateTime::currentDateTime();
    picname=datetime.toString("yyyyMMddhhmmss");
    if(picname==lasttime)
    {
        count++;
        lasttime=picname;
        QString countstr=QString::number(count,10);
        QString filename = userName + "/" + userHand + "/" + picname + countstr + ".png";
        qImage.save(filename);
    }
    else
    {
        count=1;
        lasttime=picname;
        QString countstr=QString::number(count,10);
        QString filename = userName + "/" + userHand + "/" + picname + countstr + ".png";
        qImage.save(filename);
    }
}


