#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cl = new chatClient(MAINWINDOW,this);

    //you may explain what's the function of these two connect.
    connect(cl, SIGNAL(newMessageRead(const QString&)), this, SLOT(add_new_msg(const QString&)));
    connect(this, SIGNAL(newMessageSent(const QString &)), this, SLOT(add_new_msg(const QString &)));

    setWindowTitle("ChatWindow");
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

//connect to server, ip and port is hard coded, you may add a input box
//to connect to the ip you want
void MainWindow::on_actionConnect_To_Server_triggered(){
    cl->connectToServer("127.0.0.1", 6666);
    //emit newMessageSent("Successfully connnet to server.");//这里未实现条件显示这一句。
}

//show message on textbrowser
void MainWindow::add_new_msg(const QString &newMsg){
    QString old = ui->info_text->toPlainText();
    old += (newMsg + "\n");
    ui->info_text->setText(old);
    ui->info_text->setFocus();
}



