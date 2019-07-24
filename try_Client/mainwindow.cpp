#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString x_IP, uint16_t x_port,QString xname,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),name(xname)
{
    ui->setupUi(this);
    cl = new chatClient(MAINWINDOW,this);
    setWindowTitle("ChatWindow");

    //you may explain what's the function of these two connect.
    connect(cl, SIGNAL(newMessageRead(const QString&)), this, SLOT(add_new_msg(const QString&)));
    connect(this, SIGNAL(newMessageSent(const QString &)), this, SLOT(add_new_msg(const QString &)));

    cl->connectToServer(x_IP,x_port);

    cl->sendMessage(QString("MW") + name);
}

//destroy
MainWindow::~MainWindow()
{
    delete ui;
    if(cl != nullptr)
        delete cl;
}


//send button clicked
void MainWindow::on_send_button_clicked(){
    QString toSend = ui->input_text->toPlainText();
    cl->sendMessage(toSend);
    ui->input_text->clear();
    ui->input_text->setFocus();
    QString msgTmp = "you:" + toSend;
    emit newMessageSent(msgTmp); //what's this?
}

//show message on textbrowser
void MainWindow::add_new_msg(const QString &newMsg){
    QString old = ui->info_text->toPlainText();
    old += (newMsg + "\n");
    ui->info_text->setText(old);
    ui->info_text->setFocus();
}



