#include "login.h"
#include "ui_login.h"

Login::Login(QString x_IP, uint16_t x_port, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login),con_IP(x_IP),con_port(x_port),isconneted(false)
{
    ui->setupUi(this);
    cl = new chatClient(LOGIN,this);

    ui->User_password->setEchoMode(QLineEdit::Password);
    setWindowTitle("Login");

    //connect
    connect(ui->Cancel_pushbutton,SIGNAL(clicked()),this,SLOT(quit_and_close()));
    connect(cl,SIGNAL(login_info(const QString&)),this,SLOT(display_loginstate(const QString&)));

}

Login::~Login()
{
    delete ui;
    if(cl != nullptr)delete cl;
}

void Login::on_Register_clicked()
{
    Register r(con_IP,con_port);
    r.show();
    r.exec();
}

void Login::on_Login_pushbutton_clicked()
{
    if( ui->User_name->text().isEmpty() )
    {
        QMessageBox::warning(this, tr("Warning"), tr("User name cannot be empty"));
        return;
    }else if(ui->User_password->text().isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Password cannot be empty"));
        return;
    }

    name = ui->User_name->text();
    QString passw_hash = QCryptographicHash::hash( ui->User_password->text().toUtf8(),
                                                      QCryptographicHash::Sha3_256 );

    QString tosend;
    //connet to server + Encode
    if(!isconneted){
        cl->connectToServer(con_IP, con_port);
        isconneted = true;
        tosend = "LI" + name +" "+ passw_hash;
    }else tosend = name +" "+ passw_hash;

    cl->sendMessage(tosend);
    return;
}

void Login::display_loginstate(const QString&s){
    if(s == "Success"){
        QMessageBox::about
                (this,"Message from server","Hi "+name+QString("! \nYou have successfully logined! "));
       accept();
    }else if(s == "Logined"){
        QMessageBox::warning
                (this,tr("Warning"),tr("This user has already logined!"));
        ui->User_password->clear();
        ui->User_password->setFocus();
        ui->User_name->clear();
        ui->User_name->setFocus();
        return;
    } else if(s == "WrongPassword"){
        QMessageBox::warning
                (this,tr("Warning"),tr("Wrong Password!"));
        ui->User_password->clear();
        ui->User_password->setFocus();
        return;
    }else if(s == "Notexist"){
        QMessageBox::warning(this,tr("Warning"),tr("This user hasn't registered! "));
        ui->User_name->clear();
        ui->User_name->setFocus();
        ui->User_password->clear();
        ui->User_password->setFocus();
        return;
    }
}

QString Login::getName(){
    return name;
}

void Login::quit_and_close(){
    cl->disconnect();
    close();
}
QString Login::getIP(){
    return con_IP;
}

uint16_t Login::getPort(){
    return con_port;
}

/*
void Login::Run_mainwindow(){
    MainWindow w(con_IP,con_port,name);
    w.show();
    a->exec();
}
*/
