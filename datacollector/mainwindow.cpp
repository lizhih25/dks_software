#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString MainWindow::cImageDir = QString("/image/");
const QString MainWindow::cVideoDir = QString("/video/");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QShortcut  *m_ALT_c_Accel= new QShortcut(Qt::Key_C, this);
    connect(m_ALT_c_Accel, SIGNAL(activated()), this, SLOT(change_configure()));

    QShortcut  *m_ALT_d_Accel= new QShortcut(Qt::Key_D, this);
    connect(m_ALT_d_Accel, SIGNAL(activated()), this, SLOT(change_rootDir()));

    QShortcut  *m_ALT_0_Accel= new QShortcut(Qt::Key_0, this);
    connect(m_ALT_0_Accel, SIGNAL(activated()), this, SLOT(change_camera_0()));
    QShortcut  *m_ALT_1_Accel= new QShortcut(Qt::Key_1, this);
    connect(m_ALT_1_Accel, SIGNAL(activated()), this, SLOT(change_camera_1()));
    QShortcut  *m_ALT_2_Accel= new QShortcut(Qt::Key_2, this);
    connect(m_ALT_2_Accel, SIGNAL(activated()), this, SLOT(change_camera_2()));

    QShortcut  *m_ALT_enter_Accel= new QShortcut(Qt::Key_Return, this);
    connect(m_ALT_enter_Accel, SIGNAL(activated()), this, SLOT(on_imagebutton_clicked()));
    QShortcut  *m_ALT_space_Accel= new QShortcut(Qt::Key_Space, this);
    connect(m_ALT_space_Accel, SIGNAL(activated()), this, SLOT(on_videobutton_clicked()));


    mConfigFileName = QString("config.xml");
    loadConfigure(mConfigFileName);

    miImage=1;
    miVideoFrame=0;
    mLastTimeString = QDateTime::currentDateTime().toString("yyyy");

    ui->videobutton->setEnabled(true);
    ui->markCheckBox->setCheckState(Qt::Unchecked);
    ui->userHandComboBox->setCurrentIndex(0);
    on_userHandComboBox_currentIndexChanged(0);

    mShowingCapture.open(0);   //设置摄像头
}

MainWindow::~MainWindow()
{
    mShowingCapture.release();
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(mShowingCapture.isOpened()) {
        mShowingCapture >> mCapturedMat;
        if (ui->markCheckBox->isChecked()){
            mRocExtractor.setSrcImage(mCapturedMat);
            mTempMat = mRocExtractor.getRocImage();
            cv::cvtColor(mTempMat, mTempMat, CV_BGR2RGB);
        }
        else{
            cv::cvtColor(mCapturedMat, mTempMat, CV_BGR2RGB);
        }
        mDisplayImage=QImage((const unsigned char*)(mTempMat.data),
                             mTempMat.cols,
                             mTempMat.rows,
                             QImage::Format_RGB888);
        ui->labelVideo->setPixmap(QPixmap::fromImage(mDisplayImage));
        if(ui->videobutton->isEnabled());
        else {
            if (miVideoFrame < cRecordFps*cReordTimeLength){
                mRecordVideo << mCapturedMat;
                miVideoFrame++;
            }
            else {
                mRecordVideo << mCapturedMat;
                ui->videobutton->setEnabled(true);
                miVideoFrame=0;
            }
        }
    }
}

void MainWindow::on_imagebutton_clicked()
{
    /// 判断目录是否存在，不存在便新建
    QString saveDir(ui->userNameLineEdit->text() + cImageDir + mUserHand);
    qDebug() << saveDir;
    if(mRootSaveDir.exists(saveDir) == false) mRootSaveDir.mkpath(saveDir);

    QString mTimeString=QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    if (mTimeString.compare(mLastTimeString) == 0) {
        miImage = (miImage==9)?9:(miImage+1);
    }
    else {
        miImage = 1;
        mLastTimeString = mTimeString;
    }
    QString countstr=QString::number(miImage,10);
    QString mImageName = mRootSaveDir.path()+"/"+saveDir+ "/"+mTimeString+countstr+".png";
    cv::imwrite(mImageName.toAscii().data(), mCapturedMat);
}

void MainWindow::on_videobutton_clicked()
{
    if (ui->videobutton->isEnabled()==false) return;
    /// 判断目录是否存在，不存在便新建
    QString saveDir(ui->userNameLineEdit->text() + cVideoDir + mUserHand);
    qDebug() << saveDir;
    if(mRootSaveDir.exists(saveDir) == false) mRootSaveDir.mkpath(saveDir);

    QString mTimeString = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QString mVideoName=mRootSaveDir.path()+"/"+saveDir+"/"+mTimeString+".avi";
    int fcc=CV_FOURCC('M','J','P','G');
    bool isColor = true;
    mRecordVideo.open(mVideoName.toAscii().data(), fcc, cRecordFps, mCapturedMat.size(), isColor);

    ui->videobutton->setDisabled(true);
}

void MainWindow::change_camera(int camid)
{
    mShowingCapture.open(camid);
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

void MainWindow::loadConfigure(QString configureFileName)
{
    cv::FileStorage conf;
    if (QFile(configureFileName).exists()) {
        qDebug() << "There is a configure file.";
        conf.open(configureFileName.toAscii().data(),cv::FileStorage::READ);
        if (conf.isOpened()==false) {
            qDebug() << "Failed to open exist config file!";
        }
        std::string tempStr;
        conf["root_dir"] >> tempStr;
        conf.release();
        mRootSaveDir = QDir(QString::fromStdString(tempStr));
        return;
    }
    qDebug() << "There is no configure file.";
    mRootSaveDir = QDir::currentPath();
    conf.open(configureFileName.toAscii().data(), cv::FileStorage::WRITE);
    if (conf.isOpened() == false) {
        qDebug() << "Failed to open created config file!";
    }
    conf << "root_dir" << mRootSaveDir.absolutePath().toAscii().data();
    conf.release();
}

void MainWindow::change_configure()
{
    QString newConfigFileName =
            QFileDialog::getOpenFileName(this,
                                         tr("Open Config File"),
                                         QDir::homePath(),
                                         tr("Configure File (*.xml *.yml *.yaml)"));
    if (newConfigFileName.data()->isNull()) {
        qDebug() << "There is no new configure file!";
    }
    loadConfigure(newConfigFileName);
}

void MainWindow::on_userHandComboBox_currentIndexChanged(int index)
{
    mUserHand=(index==0)?"l":"r";
}

void MainWindow::change_rootDir()
{
    QString rootDir =
            QFileDialog::getExistingDirectory(this,
                                              tr("Select New Root Dir"),
                                              mRootSaveDir.absolutePath());
    if (rootDir.data()->isNull()) return;
    mRootSaveDir = QDir(rootDir);
    cv::FileStorage conf(mConfigFileName.toAscii().data(), cv::FileStorage::WRITE);
    if (conf.isOpened() == false) {
        qDebug() << "Failed to open created config file!";
    }
    conf << "root_dir" << mRootSaveDir.absolutePath().toAscii().data();
    conf.release();
}
