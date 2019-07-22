#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    cl = new chatClient(this);

    ui->password->setEchoMode(QLineEdit::Password);
    ui->password_confirm->setEchoMode(QLineEdit::Password);

    setWindowTitle("Register");
}

Register::~Register()
{
    delete ui;
    if(cl != nullptr) delete cl;
}

void Register::on_Confirm_clicked()
{
    //这里判断的时候真的是有点傻。如果在判断失误之后能继续输入就好了
    if( ui->user_name->text().isEmpty() )
    {
        QMessageBox::warning(this, tr("Warning"), tr("User name cannot be empty"));
        return;
    }else if(ui->password->text().isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Password cannot be empty"));
        return;
    }else if(ui->password->text().isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Please confirm your password"));
        return;
    }
    QString user_name = ui->user_name->text();
    QString passw_hash = QCryptographicHash::hash( ui->password->text().toUtf8(),
                                                      QCryptographicHash::Sha3_256 );
    QString passwcon_hash = QCryptographicHash::hash( ui->password_confirm->text().toUtf8(),
                                                      QCryptographicHash::Sha3_256 );
    if(passw_hash != passwcon_hash){
        QMessageBox::warning(this, tr("Warning"), tr("Entered passwords differ"));
        return;
    }
    QString tosend = "RG" + user_name +" "+ passwcon_hash;
    //本步骤应该交给login去做。
    cl->connectToServer("127.0.0.1", 6666);
    cl->sendMessage(tosend);
    QMessageBox::about(this,"Welcome", "You have successfully Registered!  ");
    //本步骤应该直接返回login界面
    return;
}

void Register::on_Return_clicked()
{

}