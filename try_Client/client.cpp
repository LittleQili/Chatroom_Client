#include "client.h"
//You may explain how QSocket works if you use these codes.
chatClient::chatClient(WindowT w, QObject *parent) : QObject(parent)
{
    this->sock = new QTcpSocket(this);
    switch (w) {
    case CONFIRMIP:
        connect(sock,SIGNAL(readyRead()),this,SLOT(ipwindow_readMsg()));
        break;
    case LOGIN:
        connect(sock,SIGNAL(readyRead()),this,SLOT(login_readMsg()));
        break;
    case REGISTER:
        connect(sock,SIGNAL(readyRead()),this,SLOT(regwindow_readMsg()));
        break;
    case MAINWINDOW:
        connect(sock, SIGNAL(readyRead()), this, SLOT(mw_readMsg()));
        break;
    case CHANGENAME:
        connect(sock, SIGNAL(readyRead()), this, SLOT(ch_name_readMsg()));
        break;
    case CHANGEPSWD:
        connect(sock, SIGNAL(readyRead()), this, SLOT(ch_pswd_readMsg()));
        break;
    case ADMINCHOSE:
        connect(sock, SIGNAL(readyRead()), this, SLOT(am_chos_readMsg()));
        break;
    default:
        break;
    }
}

void chatClient::connectToServer(QString ip, uint16_t port){
    sock->connectToHost(ip, port);
}

void chatClient::sendMessage(QString msg){
    sock->write(msg.toLocal8Bit());
    sock->waitForBytesWritten();
    return;
}

void chatClient::mw_readMsg(){
    QString receivedMsg = QString::fromUtf8(sock->readAll());
    emit newMessageRead(receivedMsg);
}

chatClient::~chatClient(){
    if(sock != nullptr) delete sock;
}

void chatClient::ipwindow_readMsg(){
    QString receivedMsg = QString::fromUtf8(sock->readAll());
    emit ipwindow_isconnect(receivedMsg);
}

void chatClient::regwindow_readMsg(){
    QString receivedMsg = QString::fromUtf8(sock->readAll());
    emit regwindow_issuccess(receivedMsg);
}

void chatClient::login_readMsg(){
    QString receivedMsg = QString::fromUtf8(sock->readAll());
    emit login_info(receivedMsg);
}

void chatClient::ch_name_readMsg(){
    QString receivedMsg = QString::fromUtf8(sock->readAll());
    emit ch_name_info(receivedMsg);
}

void chatClient::ch_pswd_readMsg(){
    QString receivedMsg = QString::fromUtf8(sock->readAll());
    emit ch_pswd_info(receivedMsg);
}

void chatClient::am_chos_readMsg(){
    QString receivedMsg = QString::fromUtf8(sock->readAll());
    emit am_chos_info(receivedMsg);
}
