#include "register.h"
#include "ui_register.h"

Register::Register(QString x_IP, uint16_t x_port, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register),con_IP(x_IP),con_port(x_port),isconnected(false)
{
    ui->setupUi(this);
    cl = new chatClient(REGISTER,this);

    ui->password->setEchoMode(QLineEdit::Password);
    ui->password_confirm->setEchoMode(QLineEdit::Password);

    connect(cl,SIGNAL(regwindow_issuccess(const QString&)),this,SLOT(display_issuccess(const QString&)));
    connect(ui->Return,SIGNAL(clicked()),this,SLOT(quit_and_close()));

    setWindowTitle("Register");
}

Register::~Register()
{
    delete ui;
    if(isconnected)cl->disconnect();
    if(cl != nullptr){
        delete cl;
    }
}

void Register::on_Confirm_clicked()
{
    if( ui->user_name->text().isEmpty() )
    {
        QMessageBox::warning(this, tr("Warning"), tr("User name cannot be empty"));
        return;
    }else if(ui->password->text().isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Password cannot be empty"));
        return;
    }else if(ui->password_confirm->text().isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Please confirm your password"));
        return;
    }
    //name
    QString user_name = ui->user_name->text();
    std::string namejudge = user_name.toStdString();
    int pos = namejudge.find(" ");
    if(pos != -1){
        QMessageBox::warning(this, tr("Warning"), tr("Invalid name: it shouldn't contain space! "));
        ui->user_name->clear();
        ui->user_name->setFocus();
        return;
    }
    //password
    QString passw_hash = QCryptographicHash::hash( ui->password->text().toUtf8(),
                                                      QCryptographicHash::Sha3_256 );
    QString passwcon_hash = QCryptographicHash::hash( ui->password_confirm->text().toUtf8(),
                                                      QCryptographicHash::Sha3_256 );
    if(passw_hash != passwcon_hash){
        QMessageBox::warning(this, tr("Warning"), tr("Entered passwords differ"));
        ui->password_confirm->clear();
        ui->password_confirm->setFocus();
        return;
    }
    //Encode
    QString tosend = user_name +" "+ passwcon_hash;
    //connect
    if(!isconnected){
        cl->connectToServer(con_IP, con_port);
        cl->sendMessage("RG"+tosend);
        isconnected = true;
    }else{
        cl->sendMessage(tosend);
    }
    return;
}

void Register::display_issuccess(const QString& s){
    if(s == "Success"){
        QMessageBox::about(this,"Message from server","You have successfully registered! ");
        emit ui->Return->clicked();
    }else if(s == "Fail"){
        QMessageBox::warning(this, tr("Warning"), tr("The name has been used by other people! "));
        ui->user_name->clear();
        ui->user_name->setFocus();
    }
}

void Register::quit_and_close(){
    if(isconnected)cl->disconnect();
    close();
}
