#include "mainwindow.h"
#include "confirmip.h"
#include <QApplication>
//need no modification
//yummy???
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Login(include register)
    //if（success）
    ConfirmIP con;
    con.show();
    //Register r;
    //r.show();
    //MainWindow w;
    //w.show();
    return a.exec();
}
