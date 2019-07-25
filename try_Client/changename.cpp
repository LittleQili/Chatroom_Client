#include "changename.h"
#include "ui_changename.h"

ChangeName::ChangeName(QString x_IP, uint16_t x_port, QString xname, MainWindow* xmw, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeName),name(xname),con_IP(x_IP),con_port(x_port),isconnected(false),mw(xmw)
{
    ui->setupUi(this);
    cl = new chatClient(CHANGENAME,this);

    ui->Password->setEchoMode(QLineEdit::Password);
    setWindowTitle(name + " : Change your name");

    //connect(this,SIGNAL(nameChanged(const QString&)),mw,SLOT(name_changed(const QString&)));
    connect(ui->Cancel,SIGNAL(clicked()),this,SLOT(quit_and_close()));
    connect(cl,SIGNAL(ch_name_info(const QString&)),this,SLOT(display_issuccess(const QString&)));

}

ChangeName::~ChangeName()
{
    delete ui;
    if(cl != nullptr)delete cl;
}

void ChangeName::quit_and_close(){
    if(isconnected)cl->disconnect();
    close();
}

void ChangeName::on_Ok_clicked()
{
    if( ui->Password->text().isEmpty() )
    {
        QMessageBox::warning(this, tr("Warning"), tr("Password cannot be empty!"));
        return;
    }else if(ui->NewName->text().isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("New name cannot be empty!"));
        return;
    }
    //name
    newname = ui->NewName->text();
    std::string namejudge = newname.toStdString();
    int pos = namejudge.find(" ");
    if(pos != -1){
        QMessageBox::warning(this, tr("Warning"), tr("Invalid name: it shouldn't contain space! "));
        ui->NewName->clear();
        ui->NewName->setFocus();
        return;
    }
    if(newname == name){
        QMessageBox::warning(this, tr("Warning"), tr("The name you entered is the same as before.\nIf you don't want to change it, just click \"Cancel\"."));
        return;
    }
    //password
    QString passw_hash = QCryptographicHash::hash( ui->Password->text().toUtf8(),
                                                      QCryptographicHash::Sha3_256 );

    QString tosend = name + " " + newname + " " +passw_hash;
    if(isconnected){
        cl->sendMessage(tosend);
    }else{
        cl->connectToServer(con_IP,con_port);
        cl->sendMessage("CN" + tosend);
        isconnected = true;
    }
    return;
}

void ChangeName::display_issuccess(const QString&s){
    if(s == "Success"){
        QMessageBox::about(this,"Message from server","You have successfully change your name to " + newname +" !");
        mw->name_changed(newname);
        emit ui->Cancel->clicked();
    }else if(s == "WrongPassword"){
        QMessageBox::warning(this, tr("Warning"), tr("You have entered wrong password !"));
        ui->Password->clear();
        ui->Password->setFocus();
    }else if(s == "NameExist"){
        QMessageBox::warning(this, tr("Warning"), tr("This name has been used by others !"));
        ui->NewName->clear();
        ui->NewName->setFocus();
    }
}
