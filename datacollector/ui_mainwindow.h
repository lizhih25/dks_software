/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Oct 20 16:55:08 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *labelVideo;
    QLabel *label;
    QLineEdit *userNameLineEdit;
    QLabel *label_2;
    QComboBox *userHandComboBox;
    QPushButton *videobutton;
    QPushButton *imagebutton;
    QCheckBox *markCheckBox;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(643, 489);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        labelVideo = new QLabel(centralWidget);
        labelVideo->setObjectName(QString::fromUtf8("labelVideo"));
        labelVideo->setGeometry(QRect(10, 10, 480, 360));
        labelVideo->setFrameShape(QFrame::StyledPanel);
        labelVideo->setScaledContents(true);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(510, 30, 61, 16));
        userNameLineEdit = new QLineEdit(centralWidget);
        userNameLineEdit->setObjectName(QString::fromUtf8("userNameLineEdit"));
        userNameLineEdit->setGeometry(QRect(510, 50, 113, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(510, 80, 61, 16));
        userHandComboBox = new QComboBox(centralWidget);
        userHandComboBox->setObjectName(QString::fromUtf8("userHandComboBox"));
        userHandComboBox->setGeometry(QRect(510, 100, 111, 22));
        videobutton = new QPushButton(centralWidget);
        videobutton->setObjectName(QString::fromUtf8("videobutton"));
        videobutton->setGeometry(QRect(510, 250, 75, 23));
        imagebutton = new QPushButton(centralWidget);
        imagebutton->setObjectName(QString::fromUtf8("imagebutton"));
        imagebutton->setGeometry(QRect(510, 210, 75, 23));
        markCheckBox = new QCheckBox(centralWidget);
        markCheckBox->setObjectName(QString::fromUtf8("markCheckBox"));
        markCheckBox->setGeometry(QRect(520, 310, 71, 16));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        labelVideo->setText(QString());
        label->setText(QApplication::translate("MainWindow", "user name:", 0, QApplication::UnicodeUTF8));
        userNameLineEdit->setText(QApplication::translate("MainWindow", "test", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "user hand:", 0, QApplication::UnicodeUTF8));
        userHandComboBox->clear();
        userHandComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "l", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "r", 0, QApplication::UnicodeUTF8)
        );
        videobutton->setText(QApplication::translate("MainWindow", "video", 0, QApplication::UnicodeUTF8));
        imagebutton->setText(QApplication::translate("MainWindow", "image", 0, QApplication::UnicodeUTF8));
        markCheckBox->setText(QApplication::translate("MainWindow", "Mark", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
