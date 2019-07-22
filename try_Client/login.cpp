#include "login.h"
#include "register.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    cl = new chatClient(this);

    ui->User_password->setEchoMode(QLineEdit::Password);

    //connect

    //choose IP

}
Login::Login(chatClient *xcl,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    cl = xcl;

    ui->User_password->setEchoMode(QLineEdit::Password);

    //connect

    //choose IP

}

Login::~Login()
{
    delete ui;
}

void Login::on_Register_clicked()
{
    Register r;
    r.show();

}
