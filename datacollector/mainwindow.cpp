#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString MainWindow::scImageDir = QString("/image/");
const QString MainWindow::scVideoDir = QString("/video/");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QShortcut  *pQShortcut_c= new QShortcut(Qt::Key_C, this);
    connect(pQShortcut_c, SIGNAL(activated()), this, SLOT(change_configure()));

    QShortcut  *pQShortcut_d= new QShortcut(Qt::Key_D, this);
    connect(pQShortcut_d, SIGNAL(activated()), this, SLOT(change_rootDir()));

    QShortcut  *pQShortcut_0= new QShortcut(Qt::Key_0, this);
    connect(pQShortcut_0, SIGNAL(activated()), this, SLOT(change_camera_0()));
    QShortcut  *pShortcut_1= new QShortcut(Qt::Key_1, this);
    connect(pShortcut_1, SIGNAL(activated()), this, SLOT(change_camera_1()));
    QShortcut  *pShortcut_2= new QShortcut(Qt::Key_2, this);
    connect(pShortcut_2, SIGNAL(activated()), this, SLOT(change_camera_2()));

    QShortcut  *pShortcut_return= new QShortcut(Qt::Key_Return, this);
    connect(pShortcut_return, SIGNAL(activated()), this, SLOT(on_imagebutton_clicked()));
    QShortcut  *pShortcut_space= new QShortcut(Qt::Key_Space, this);
    connect(pShortcut_space, SIGNAL(activated()), this, SLOT(on_videobutton_clicked()));

    miImage=1;
    miVideoFrame=0;
    mLastTimeString = QDateTime::currentDateTime().toString("yyyy");

    ui->videobutton->setEnabled(true);
    ui->markCheckBox->setCheckState(Qt::Unchecked);
    ui->userHandComboBox->setCurrentIndex(0);
    on_userHandComboBox_currentIndexChanged(0);
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
            mFovMarker.setSrcImage(mCapturedMat);
            mTempMat = mFovMarker.getMarkedImage();
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
            if (miVideoFrame < scRecordFps*scReordTimeLength){
                mRecordVideo << mCapturedMat;
                miVideoFrame++;
            }
            else {
                mRecordVideo << mCapturedMat;
                ui->videobutton->setEnabled(true);
                miVideoFrame=0;
                QString videoName("*.avi");
                QStringList files = mVideoDir.entryList(QStringList(videoName),
                                                        QDir::Files | QDir::NoSymLinks);
                ui->labelVideoCount->setText(QString(tr("%2 videos saved")).arg(files.length()));
            }
        }
    }
}

void MainWindow::on_imagebutton_clicked()
{
    /// prepare Dir for save
    QString saveDir(ui->userNameLineEdit->text() + scImageDir + mUserHand);
    qDebug() << saveDir;
    if(cfg.saveRootDir.exists(saveDir) == false) cfg.saveRootDir.mkpath(saveDir);

    QString mTimeString=QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    if (mTimeString.compare(mLastTimeString) == 0) {
        miImage = (miImage==9)?9:(miImage+1);
    }
    else {
        miImage = 1;
        mLastTimeString = mTimeString;
    }
    QString countstr=QString::number(miImage,10);
    QString mImageName = cfg.saveRootDir.path()+"/"+saveDir+ "/"+mTimeString+countstr+".png";
    cv::imwrite(mImageName.toAscii().data(), mCapturedMat);

    QDir imageDir(cfg.saveRootDir.path()+"/"+saveDir);
    QString imageName("*.png");
    QStringList files = imageDir.entryList(QStringList(imageName),
                                           QDir::Files | QDir::NoSymLinks);
    ui->labelImageCount->setText(QString(tr("%2 images saved")).arg(files.length()));
}

void MainWindow::on_videobutton_clicked()
{
    if (ui->videobutton->isEnabled()==false) return;
    /// prepare Dir for save
    QString saveDir(ui->userNameLineEdit->text() + scVideoDir + mUserHand);
    qDebug() << saveDir;
    if(cfg.saveRootDir.exists(saveDir) == false) cfg.saveRootDir.mkpath(saveDir);

    QString mTimeString = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QString mVideoName=cfg.saveRootDir.path()+"/"+saveDir+"/"+mTimeString+".avi";
    int fcc=CV_FOURCC('M','J','P','G');
    bool isColor = true;
    mRecordVideo.open(mVideoName.toAscii().data(), fcc, scRecordFps, mCapturedMat.size(), isColor);

    ui->videobutton->setDisabled(true);
    this->mVideoDir = QDir(cfg.saveRootDir.path()+"/"+saveDir);
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

void MainWindow::change_configure()
{
    QString newConfigFileName =
            QFileDialog::getOpenFileName(this,
                                         tr("Open Config File"),
                                         QDir::homePath(),
                                         tr("Configure File (*.xml *.yml *.yaml)"));
    if (newConfigFileName.data()->isNull()) {
        qDebug() << "There is no new configure file!";
        return;
    }
    cfg.load(newConfigFileName);
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
                                              cfg.saveRootDir.path());
    if (rootDir.data()->isNull()) return;
    cfg.saveRootDir = rootDir;
    cfg.save();
}

void MainWindow::optionAndConfigParse(int argc, char* argv[])
{
    /* 1. CREATE AN OBJECT */
    AnyOption *opt = new AnyOption();

    /* 2. SET PREFERENCES  */
    //opt->noPOSIX(); /* do not check for POSIX style character options */
    //opt->setVerbose(); /* print warnings about unknown options */
    //opt->autoUsagePrint(true); /* print usage for bad options */

    /* 3. SET THE USAGE/HELP   */
    opt->addUsage( "" );
    opt->addUsage( "Usage: " );
    opt->addUsage( "" );
    opt->addUsage( " -h  --help               Prints this help " );
    opt->addUsage( " -0        	              Uses camera No.0 ");
    opt->addUsage( " -1                       Uses camera No.1 ");
    opt->addUsage( " -2        	              Uses camera No.2 ");
    opt->addUsage( "     --camera 0	          Uses camera No.0 ");
    opt->addUsage( " -c  --config config.xml  Config File Name ");
    opt->addUsage( " -d  --dir saveDir        Dir to Save Images and Videos ");
    opt->addUsage( " -l  --log                Displays log window ");
    opt->addUsage( "" );

    /* 4. SET THE OPTION STRINGS/CHARACTERS */

    /* by default all  options  will be checked on the command line and from option/resource file */
    opt->setFlag(  "help", 'h' );   /* a flag (takes no argument), supporting long and short form */
    opt->setFlag(  '0' );   /* a flag (takes no argument), supporting long and short form */
    opt->setFlag(  '1' );   /* a flag (takes no argument), supporting long and short form */
    opt->setFlag(  '2' );   /* a flag (takes no argument), supporting long and short form */
    opt->setOption(  "camera" );      /* an option (takes an argument), supporting only long form */
    opt->setOption(  "config", 'c' ); /* an option (takes an argument), supporting long and short form */
    opt->setOption(  "dir", 'd' ); /* an option (takes an argument), supporting long and short form */
    opt->setFlag(  "log", 'l' );   /* a flag (takes no argument), supporting long and short form */

    /* 5. PROCESS THE COMMANDLINE AND RESOURCE FILE */

    /* go through the command line and get the options  */
    opt->processCommandArgs( argc, argv );

    /* 6. GET THE VALUES */
    if( opt->getFlag( "help" ) || opt->getFlag( 'h' ) ){
        opt->printUsage();
        exit(1);
    }
    /// parse arguments about camera \n
    /// the priority is
    /// 1. -0
    /// 2. -1
    /// 3. -2
    /// 4. -camera x
    /// and the default is 0
    int cameraId = 0;
    if( opt->getValue( "camera" ) != NULL ) {
        int newCamId = QString(opt->getValue( "camera" )).toInt();
        if ( (newCamId >=0) && (newCamId <= 4))
            cameraId = newCamId;
    }
    if( opt->getFlag( '2' ) )
        cameraId = 2 ;
    if( opt->getFlag( '1' ) )
        cameraId = 1 ;
    if( opt->getFlag( '0' ) )
        cameraId = 0 ;
    mShowingCapture.open(cameraId);

    /// load config file first change the dir if there is a dir argument
    if( opt->getValue( 'c' ) != NULL  || opt->getValue( "config" ) != NULL  ) {
        qDebug() << "get the config argument: " <<QString(opt->getValue('c'));
        if (cfg.load(QString( opt->getValue( 'c' ) )) == false)
            cfg.createDefault();
    }
    else {/// defualt  using "config.xml" file in current dir.
        qDebug() << "did not get the config argument!";
        if (cfg.load(QString("config.xml")) == false)
            cfg.createDefault();
    }


    /// override the config file if there is a dir argument
    if( opt->getValue( 'd' ) != NULL  || opt->getValue( "dir" ) != NULL  ) {
        cfg.saveRootDir = QDir(QString( opt->getValue( 'd' ) ));
        cfg.save();
    }

    /// log window is not implemented
    /// \todo add a modeless log window
    if( opt->getFlag( 'l' ) || opt->getFlag( "log" ) )
        qDebug() << "The log window is activated.";

    /* 8. DONE */
    delete opt;
}

