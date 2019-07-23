#include "confirmip.h"
#include "ui_confirmip.h"

ConfirmIP::ConfirmIP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmIP)
{
    ui->setupUi(this);
    cl = new chatClient(CONFIRMIP,this);

    connect(cl,SIGNAL(ipwindow_isconnect(const QString&)),this,SLOT(display_isconnected(const QString&)));

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

    con_IP = ui->IPaddr->text();
    if(ui->Port->text() == "6666")con_port = 6666;
    cl->connectToServer(con_IP,con_port);
    cl->sendMessage("IP");
}

void ConfirmIP::display_isconnected(const QString&s){
    if(s == (QString)"Success"){
        QMessageBox::about(this,"Message from server","You have successfully connect the server you want! ");
    }
}

void ConfirmIP::RunClientProcess(){

}
