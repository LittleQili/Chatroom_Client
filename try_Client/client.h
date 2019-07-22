#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QThread>

enum WindowT{
    CONFIRMIP,LOGIN,REGISTER,MAINWINDOW,
};

class chatClient : public QObject
{
    Q_OBJECT

public:
    explicit chatClient(WindowT w,QObject *parent = nullptr);
    ~chatClient();

private:
    QTcpSocket *sock = nullptr;

signals:
    void newMessageRead(const QString&);
    void ipwindow_isconnect(const QString&);
public slots:
    void readMsg();
    void ipwindow_readMsg();
public:
    void connectToServer(QString ip, uint16_t port);
    void sendMessage(QString msg);
};

#endif // CLIENT_H
