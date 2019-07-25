#ifndef LOGIN_H
#define LOGIN_H

#include "register.h"
#include "mainwindow.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QString x_IP, uint16_t x_port,QWidget *parent = 0);
    ~Login();

private slots:
    void on_Register_clicked();
    void display_loginstate(const QString&);
    void on_Login_pushbutton_clicked();
    void quit_and_close();

private:
    Ui::Login *ui;
    chatClient *cl;
    QString con_IP;
    uint16_t con_port;

    QString name;

    bool isconneted;

    //void Run_mainwindow();
public:
    QString getName();
    QString getIP();
    uint16_t getPort();
};

#endif // LOGIN_H
