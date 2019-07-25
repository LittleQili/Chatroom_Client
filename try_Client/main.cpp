#include "mainwindow.h"
#include "confirmip.h"
//need no modification
//yummy???
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ConfirmIP con(&a);
    con.show();
    if(con.exec() == QDialog::Accepted){
        Login l(con.getIP(),con.getPort());
        l.show();
        con.close();
        if(l.exec() == QDialog::Accepted){
            MainWindow m(l.getIP(),l.getPort(),l.getName());
            m.show();
            return a.exec();
        }
    }
    return 0;
}
