#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString x_IP, uint16_t x_port,QString xname,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),name(xname),con_IP(x_IP),con_port(x_port),isadmin(false),isprivate(false)
{
    ui->setupUi(this);
    cl = new chatClient(MAINWINDOW,this);
    setWindowTitle("ChatWindow");

    //you may explain what's the function of these two connect.
    connect(cl, SIGNAL(newMessageRead(const QString&)), this, SLOT(add_new_msg(const QString&)));
    connect(this, SIGNAL(newMessageSent(const QString &)), this, SLOT(add_new_msg(const QString &)));
    connect(ui->menuMenu_Administrator,SIGNAL(hovered()),this,SIGNAL(onAdminmenu()));
    connect(ui->menuMenu_Administrator,SIGNAL(clicked()),this,SIGNAL(onAdminmenu()));

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
}

//show message on textbrowser
void MainWindow::add_new_msg(const QString &newMsg){
    if(newMsg.contains("Congratulation! You become the administrator of this chatroom!")){
        isadmin = true;
    }
    QString old = ui->info_text->toPlainText();
    old += (newMsg + "\n");
    ui->info_text->setText(old);
    ui->info_text->setFocus();
    QScrollBar *vScrollBar = ui->info_text->verticalScrollBar();
    if(vScrollBar != nullptr)vScrollBar->setValue(vScrollBar->maximum());
}

void MainWindow::on_actionLog_out_triggered(){
    if(isadmin){
        AdminChoose adc("logout",con_IP,con_port,name);
        adc.show();
        adc.exec();
    }
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

void MainWindow::on_actionChange_your_password_triggered()
{
    ChangePassword chp(con_IP,con_port,name);
    chp.show();
    chp.exec();
}

void MainWindow::onAdminmenu(){
    if(!isadmin)
        ui->menuMenu_Administrator->hide();
}
void MainWindow::clickAdminmenu(){
    if(!isadmin)
        QMessageBox::warning(this, tr("Warning"), tr("Sorry! You don't have the permission to access this."));
}

void MainWindow::on_actionChange_the_status_of_the_Chatroom_triggered()
{
    if(!isadmin)
        QMessageBox::warning(this, tr("Warning"), tr("Sorry! You don't have the permission to access this."));
    else{
        ChoosePrivate chp(this);
        chp.show();
        chp.exec();
    }
}
void MainWindow::set_public(){
    if(isprivate){
        cl->sendMessage("PPPublic");
        isprivate = false;
    }
}

void MainWindow::set_private(){
    if(!isprivate){
        cl->sendMessage("PPPrivate");
        isprivate = true;
    }
}
