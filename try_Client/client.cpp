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
        break;
    case REGISTER:
        break;
    case MAINWINDOW:
        connect(sock, SIGNAL(readyRead()), this, SLOT(readMsg()));
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

void chatClient::readMsg(){
    QString receivedMsg = QString::fromUtf8(sock->readAll());
    QString msgToHandle = "server:" + receivedMsg;
    emit newMessageRead(msgToHandle);
}

chatClient::~chatClient(){
    if(sock != nullptr) delete sock;
}

void chatClient::ipwindow_readMsg(){
    QString receivedMsg = QString::fromUtf8(sock->readAll());
    emit ipwindow_isconnect(receivedMsg);
}

