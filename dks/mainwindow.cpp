#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QShortcut  *m_ALT_enter_Accel= new QShortcut(Qt::Key_Return, this);
    connect(m_ALT_enter_Accel, SIGNAL(activated()), this, SLOT(on_imagebutton_clicked()));
    QShortcut  *m_ALT_space_Accel= new QShortcut(Qt::Key_Space, this);
    connect(m_ALT_space_Accel, SIGNAL(activated()), this, SLOT(on_videobutton_clicked()));
    QShortcut  *m_ALT_0_Accel= new QShortcut(Qt::Key_0, this);
    connect(m_ALT_0_Accel, SIGNAL(activated()), this, SLOT(change_camera_0()));
    QShortcut  *m_ALT_1_Accel= new QShortcut(Qt::Key_1, this);
    connect(m_ALT_1_Accel, SIGNAL(activated()), this, SLOT(change_camera_1()));
    QShortcut  *m_ALT_2_Accel= new QShortcut(Qt::Key_2, this);
    connect(m_ALT_2_Accel, SIGNAL(activated()), this, SLOT(change_camera_2()));
    imagecount=1;
    videocount=0;
    ui->videobutton->setEnabled(true);
    ui->markCheckBox->setCheckState(Qt::Unchecked);

    showingCapture.open(0);   //设置摄像头
}

MainWindow::~MainWindow()
{
    showingCapture.release();
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(showingCapture.isOpened()) {
        showingCapture >> capturedMat;
        if (ui->markCheckBox->isChecked()){
            rocExtractor.setSrcImage(capturedMat);
            tempMat = rocExtractor.getRocImage();
            cv::cvtColor(tempMat, tempMat, CV_BGR2RGB);
        }
        else{
            cv::cvtColor(capturedMat, tempMat, CV_BGR2RGB);
        }
        displayImage=QImage((const unsigned char*)(tempMat.data),
                            tempMat.cols,
                            tempMat.rows,
                            QImage::Format_RGB888);
        ui->labelVideo->setPixmap(QPixmap::fromImage(displayImage));
        if(ui->videobutton->isEnabled());
        else {
            if (videocount<FPS*TIME){
                recordVideo << capturedMat;
                videocount++;
            }
            else {
                recordVideo << capturedMat;
                ui->videobutton->setEnabled(true);
                videocount=0;
            }
        }
    }
}

void MainWindow::on_imagebutton_clicked()
{
    QString userName=ui->userNameLineEdit->text();
    QString userHand=ui->userHandComboBox->currentText();
    QDir *tempDir = new QDir;
    /// 判断目录是否存在，不存在便新建
    QString tempStr1(userName + "/image/l");
    if(tempDir->exists(tempStr1) == false) tempDir->mkpath(tempStr1);
    /// 判断目录是否存在，不存在便新建
    QString tempStr2(userName + "/image/r");
    if(tempDir->exists(tempStr2) == false) tempDir->mkpath(tempStr2);

    QDateTime datetime=QDateTime::currentDateTime();
    picname=datetime.toString("yyyyMMddhhmmss");
    if(picname==lasttime)
    {
        imagecount++;
        lasttime=picname;
        QString countstr=QString::number(imagecount,10);
        QString filename = userName + "/image/" + userHand + "/" + picname + countstr + ".png";
        cv::imwrite(filename.toAscii().data(), capturedMat);
    }
    else
    {
        lasttime=picname;
        QString countstr=QString::number(imagecount,10);
        QString filename = userName + "/image/" + userHand + "/" + picname + countstr + ".png";
        cv::imwrite(filename.toAscii().data(), capturedMat);
    }
}

void MainWindow::on_videobutton_clicked()
{
    if (ui->videobutton->isEnabled()==false) return;
    QString userName=ui->userNameLineEdit->text();
    QString userHand=ui->userHandComboBox->currentText();
    QDir *tempDir = new QDir;
    /// 判断目录是否存在，不存在便新建
    QString tempStr1(userName + "/video/l");
    if(tempDir->exists(tempStr1) == false) tempDir->mkpath(tempStr1);
    /// 判断目录是否存在，不存在便新建
    QString tempStr2(userName + "/video/r");
    if(tempDir->exists(tempStr2) == false) tempDir->mkpath(tempStr2);

    QDateTime datetime=QDateTime::currentDateTime();
    QString picname=userName + "/video/" + userHand + "/"+datetime.toString("yyyyMMddhhmmss")+".avi";
    QByteArray ba = picname.toLatin1();
    char *filename = ba.data();
    int fcc=CV_FOURCC('M','J','P','G');
    bool isColor = true;
    recordVideo.open(filename, fcc, FPS, capturedMat.size(), isColor);
    ui->videobutton->setDisabled(true);
}

void MainWindow::change_camera(int camid)
{
    showingCapture.open(camid);
}

void MainWindow::change_camera_0()
{
    this->change_camera(0);
}

void MainWindow::change_camera_1()
{
    this->change_camera(1);
}

void MainWindow::change_camera_2()
{
    this->change_camera(2);
}
