#include "mainwindow.h"
#include "login.h"
#include <QApplication>
//need no modification
//yummy???
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Login(include register)
    //if（success）
    Register r;
    r.show();
    MainWindow w;
    w.show();
    return a.exec();
}
