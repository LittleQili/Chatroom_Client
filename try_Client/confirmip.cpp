#include "confirmip.h"
#include "ui_confirmip.h"

ConfirmIP::ConfirmIP(QApplication* xa,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmIP),a(xa),isfirstconnect(true),isQuiry(false)
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
    cl->disconnect();
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
        con_port = ui->Port->text().toInt();
        cl->connectToServer(con_IP,con_port);
        if(isQuiry) cl->sendMessage("IPQ");
        else cl->sendMessage("IP");
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
            if(isQuiry)cl->sendMessage("IPQ");
            else cl->sendMessage("IP");
        }else if(isQuiry)cl->sendMessage("Q");
              else accept();
    }
}

void ConfirmIP::display_isconnected(const QString&s){
    if(isQuiry){
        if(s == (QString)"None"){
            QMessageBox::about(this,"Message from server","No one is in this chatroom right now.");
        }else if(s == "Private"){
            QMessageBox::warning(this, tr("Warning"), tr("Sorry, You don't have the permission to quiry this. "));
        }else QMessageBox::about(this,"Message from server","These users are in this chatroom: \n" + s);
    }else if(s == (QString)"Success"){
        QMessageBox::about(this,"Message from server","You have successfully connect the server you want!  ");
        accept();
    }

    isQuiry = false;
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


void ConfirmIP::on_Quiry_clicked()
{
    isQuiry = true;
    emit ui->OK->clicked();
}
