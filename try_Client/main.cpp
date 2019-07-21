#include "mainwindow.h"
#include <QApplication>
//need no modification
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Login(include register)
    //if（success）
    MainWindow w;
    w.show();
    return a.exec();
}
