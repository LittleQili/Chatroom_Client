#include "client.h"
//You may explain how QSocket works if you use these codes.
chatClient::chatClient(QObject *parent) : QObject(parent)
{
    this->sock = new QTcpSocket(this);
    connect(sock, SIGNAL(readyRead()), this, SLOT(readMsg()));
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

