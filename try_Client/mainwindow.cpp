#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString x_IP, uint16_t x_port,QString xname,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),name(xname),con_IP(x_IP),con_port(x_port)
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
    if(toSend.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("input shouldn't be empty! "));
        return;
    }
    cl->sendMessage("CA"+toSend);
    ui->input_text->clear();
    ui->input_text->setFocus();
    //QString msgTmp = "you:" + toSend;
    //emit newMessageSent(msgTmp); //what's this?
}

//show message on textbrowser
void MainWindow::add_new_msg(const QString &newMsg){
    QString old = ui->info_text->toPlainText();
    old += (newMsg + "\n");
    ui->info_text->setText(old);
    ui->info_text->setFocus();
    QScrollBar *vScrollBar = ui->info_text->verticalScrollBar();
    if(vScrollBar != nullptr)vScrollBar->setValue(vScrollBar->maximum());
}

void MainWindow::on_actionLog_out_triggered(){
    cl->disconnect();
    close();
    return;
}



void MainWindow::on_actionChange_your_name_triggered()
{
    ChangeName chn(con_IP,con_port,name,this);
    chn.show();
    chn.exec();
}

void MainWindow::name_changed(const QString&s){
    name = s;
    cl->sendMessage("CN"+s);
}
