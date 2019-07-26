#include "changepassword.h"
#include "ui_changepassword.h"

ChangePassword::ChangePassword(QString x_IP, uint16_t x_port, QString xname,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePassword),name(xname),con_IP(x_IP),con_port(x_port),isconnected(false)
{
    ui->setupUi(this);
    cl = new chatClient(CHANGEPSWD,this);

    ui->OldPassword->setEchoMode(QLineEdit::Password);
    ui->NewPassword->setEchoMode(QLineEdit::Password);
    ui->NewPasswordConfirm->setEchoMode(QLineEdit::Password);

    setWindowTitle(name+" : Change password");
    connect(ui->Cancel,SIGNAL(clicked()),this,SLOT(quit_and_close()));
    connect(cl,SIGNAL(ch_pswd_info(const QString&)),this,SLOT(display_issuccess(const QString&)));
}

ChangePassword::~ChangePassword()
{
    delete ui;
    if(isconnected)cl->disconnect();
    if(cl != nullptr)delete cl;
}

void ChangePassword::quit_and_close(){
    if(isconnected)cl->disconnect();
    close();
}

void ChangePassword::display_issuccess(const QString&s){
    if(s == "Success"){
        QMessageBox::about(this,"Message from server","You have successfully change your password !");
        emit ui->Cancel->clicked();
    }else if(s == "Fail"){
        QMessageBox::warning(this, tr("Warning"), tr("Wrong old password!"));
        ui->OldPassword->clear();
        ui->OldPassword->setFocus();
        return;
    }
}


void ChangePassword::on_OK_clicked()
{
    if( ui->OldPassword->text().isEmpty() )
    {
        QMessageBox::warning(this, tr("Warning"), tr("Old password name cannot be empty"));
        return;
    }else if(ui->NewPassword->text().isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("New password cannot be empty"));
        return;
    }else if(ui->NewPasswordConfirm->text().isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Please confirm your new password"));
        return;
    }
    QString oldpassw_hash = QCryptographicHash::hash( ui->OldPassword->text().toUtf8(),
                                                      QCryptographicHash::Sha3_256 );
    QString passw_hash = QCryptographicHash::hash( ui->NewPassword->text().toUtf8(),
                                                      QCryptographicHash::Sha3_256 );
    QString passwcon_hash = QCryptographicHash::hash( ui->NewPasswordConfirm->text().toUtf8(),
                                                      QCryptographicHash::Sha3_256 );
    if(passw_hash != passwcon_hash){
        QMessageBox::warning(this, tr("Warning"), tr("Entered passwords differ"));
        ui->NewPasswordConfirm->clear();
        ui->NewPasswordConfirm->setFocus();
        return;
    }
    QString tosend = name + " " + oldpassw_hash + "~#@Password@#~" + passw_hash;
    if(isconnected){
        cl->sendMessage("CP"+tosend);
    }else{
        cl->connectToServer(con_IP,con_port);
        isconnected = true;
        cl->sendMessage("CP"+tosend);
    }
    return;
}
