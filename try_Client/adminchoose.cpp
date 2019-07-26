#include "adminchoose.h"
#include "ui_adminchoose.h"

AdminChoose::AdminChoose(QString xtype,QString x_IP, uint16_t x_port, QString xname, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminChoose),name(xname),con_IP(x_IP),con_port(x_port),isconnected(false),type(xtype)
{
    ui->setupUi(this);
    cl = new chatClient(ADMINCHOSE,this);
    connect(cl,SIGNAL(am_chos_info(const QString&)),this,SLOT(readmsg(const QString&)));
    cl->connectToServer(x_IP,x_port);

    connect(ui->Cancel,SIGNAL(clicked(bool)),this,SLOT(close()));
    cl->sendMessage((QString)"AC"+type+name);
}

AdminChoose::~AdminChoose()
{
    delete ui;
    if(cl != nullptr)delete cl;
}

void AdminChoose::readmsg(const QString&s){
    if(type == "logout"){
        if(s == "None"){
            close();
        }else if(s == "Success"){
            QMessageBox::about(this,"Message from server",next_name + " becomes the administrator. ");
            close();
        }else if(s == "Notexist"){
            QMessageBox::warning(this, tr("Warning"), tr("You have entered wrong name !"));
            return ;
        }else {
            ui->info_text->setText(s);
            ui->info_text->setFocus();
            QScrollBar *vScrollBar = ui->info_text->verticalScrollBar();
            if(vScrollBar != nullptr)vScrollBar->setValue(vScrollBar->maximum());
        }
    }
}

void AdminChoose::on_OK_clicked()
{
    QString read = ui->Chooseenter->toPlainText();
    if(type == "logout"){
            if(read.contains(" ")){
                QMessageBox::warning(this, tr("Warning"), tr("You should enter only one person !"));
            }else{
                cl->sendMessage(read);
                next_name = read;
            }
            ui->Chooseenter->clear();
            ui->Chooseenter->setFocus();
    }
}
