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
    //以下语句看情况。
    if(cl != nullptr)delete cl;
}

chatClient* ConfirmIP::get_chatClient(){
    return cl;
}

void ConfirmIP::on_OK_clicked()
{
    if(ui->IPaddr->text().isEmpty()||ui->Port->text().isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Either of the box cannot be empty"));
        return;
    }

    QString tmpip = ui->IPaddr->text();
    uint16_t tmpport =uint16_t(ui->Port->text());
    cl->connectToServer(tmpip,tmpport);
}

void ConfirmIP::display_isconnected(const QString&s){

}
