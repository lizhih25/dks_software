/// own Gui front
#include <mainwindow.h>

/// Qt lib
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.optionAndConfigParse(argc, argv);
    w.show();

    return a.exec();
}
