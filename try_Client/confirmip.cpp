#include "confirmip.h"
#include "ui_confirmip.h"

ConfirmIP::ConfirmIP(QApplication* xa,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmIP),a(xa),isfirstconnect(true)
{
    ui->setupUi(this);
    cl = new chatClient(CONFIRMIP,this);

    connect(cl,SIGNAL(ipwindow_isconnect(const QString&)),this,SLOT(display_isconnected(const QString&)));
    connect(ui->Cancel,SIGNAL(clicked()),a,SLOT(quit()));

    setWindowTitle("Server Choosing");
}

ConfirmIP::~ConfirmIP()
{
    delete ui;
    if(cl != nullptr)delete cl;
}

void ConfirmIP::on_OK_clicked()
{
    if(ui->IPaddr->text().isEmpty()||ui->Port->text().isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Either of the box cannot be empty"));
        return;
    }

    if(isfirstconnect){
        con_IP = ui->IPaddr->text();
        //if(ui->Port->text() == "6666")con_port = 6666;
        con_port = ui->Port->text().toInt();
        cl->connectToServer(con_IP,con_port);
        cl->sendMessage("IP");
        isfirstconnect = false;
    }else{
        QString tmp_IP = ui->IPaddr->text();
        uint16_t tmp_port = ui->Port->text().toInt();
        if(tmp_IP != con_IP||tmp_port != con_port){
            delete cl;
            cl = new chatClient(CONFIRMIP,this);
            connect(cl,SIGNAL(ipwindow_isconnect(const QString&)),this,SLOT(display_isconnected(const QString&)));
            con_IP = tmp_IP;
            con_port = tmp_port;
            cl->connectToServer(con_IP,con_port);
            cl->sendMessage("IP");
        }
    }
}

void ConfirmIP::display_isconnected(const QString&s){
    if(s == (QString)"Success"){
        QMessageBox::about(this,"Message from server","You have successfully connect the server you want!  ");
    }
    RunClientProcess();
}

void ConfirmIP::RunClientProcess(){
    //login run.
    Login l(con_IP,con_port);
    l.show();
    if(l.exec() == QDialog :: Accepted){
        name = l.getName();
        //l.close();
        accept();
    }
}

QString ConfirmIP::getIP(){
    return con_IP;
}

uint16_t ConfirmIP::getPort(){
    return con_port;
}

QString ConfirmIP::getName(){
    return name;
}

