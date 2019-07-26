#include "chooseprivate.h"
#include "ui_chooseprivate.h"

ChoosePrivate::ChoosePrivate(MainWindow *xmw, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoosePrivate),mw(xmw)
{
    ui->setupUi(this);

    connect(ui->Private,SIGNAL(clicked()),mw,SLOT(set_private()));
    connect(ui->Public,SIGNAL(clicked()),mw,SLOT(set_public()));
    connect(ui->Private,SIGNAL(clicked()),this,SLOT(confirm_private()));
    connect(ui->Public,SIGNAL(clicked()),this,SLOT(confirm_public()));

    setWindowTitle("Chatroom State");
}

ChoosePrivate::~ChoosePrivate()
{
    delete ui;
}

void ChoosePrivate::confirm_private(){
    QMessageBox::about(this,"Message","You have successfully change this chatroom to private !");
    close();
}

void ChoosePrivate::confirm_public(){
    QMessageBox::about(this,"Message","You have successfully change this chatroom to public !");
    close();
}
