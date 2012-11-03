#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    cfg.setFileName(QString("config.xml"));
    if (cfg.load());
    else cfg.createDefault();

    demo.setDataSet(cfg.dataSetDir);

    ui->markCheckBox->setCheckState(Qt::Unchecked);

    mShowingCapture.open(0);   // finally open the camera
}

MainWindow::~MainWindow()
{
    mShowingCapture.release();
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(mShowingCapture.isOpened() == false) return;
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

void MainWindow::on_registerPushButton_clicked()
{

}

void MainWindow::on_userNameLineEdit_textChanged(const QString &arg1)
{
    this->mTestName = arg1;
}
