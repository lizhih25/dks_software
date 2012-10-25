/////////////////////////////////////////////////////////
/// \brief system configure load and write
///
/// createDefault, save and load system configure \n
/// + saveRootDir
/// + dataSetDir
///
/////////////////////////////////////////////////////////

#ifndef CONFIGURE_H
#define CONFIGURE_H

// own algorithms lib

// opencv lib
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

// Qt lib
#include <QObject>
#include <QDir>
#include <QDebug>

class Configure : public QObject
{
    Q_OBJECT
public:
    explicit Configure(QObject *parent = 0);
    bool load(QString configureFileName);
    bool load();
    bool save(QString configureFileName);
    bool save();
    bool createDefault();
    bool setFileName(QString fileName);

    QDir saveRootDir;///< The root dir for data collector to save images and videos
    QDir dataSetDir;///< The dir for demo to find the data set

signals:

public slots:

private:
    QString mConfigFileName;///< Configure file name including the path

};

#endif // CONFIGURE_H
