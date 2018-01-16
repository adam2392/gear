#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    int window_width = QApplication::desktop()->width();
//    int window_height = QApplication::desktop()->height();

    MainWindow w;
    w.show();

    return a.exec();
}
