#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QThread>

enum WindowT{
    CONFIRMIP,LOGIN,REGISTER,MAINWINDOW,CHANGENAME,CHANGEPSWD,
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
    void regwindow_issuccess(const QString&);
    void login_info(const QString&);
    void ch_name_info(const QString&);
    void ch_pswd_info(const QString&);
public slots:
    void mw_readMsg();
    void ipwindow_readMsg();
    void regwindow_readMsg();
    void login_readMsg();
    void ch_name_readMsg();
    void ch_pswd_readMsg();
public:
    void connectToServer(QString ip, uint16_t port);
    void sendMessage(QString msg);
};

#endif // CLIENT_H
