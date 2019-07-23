#include "mainwindow.h"
#include "confirmip.h"
//need no modification
//yummy???
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ConfirmIP con(&a);
    con.show();
    if(con.exec() == QDialog :: Accepted){
        MainWindow w(con.getIP(),con.getPort(),con.getName());
        w.show();
        return a.exec();
    }
    //Register r;
    //r.show();
    //MainWindow w;
    //w.show();
    return 0;
}
