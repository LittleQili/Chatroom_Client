#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDebug>
#include "client.h"
#include "mainwindow.h"

namespace Ui {
class ChangePassword;
}

class ChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePassword(QString x_IP, uint16_t x_port,QString xname,QWidget *parent = 0);
    ~ChangePassword();

private:
    Ui::ChangePassword *ui;
    chatClient *cl;
    QString name;
    QString con_IP;
    uint16_t con_port;

    bool isconnected;

private slots:
    void quit_and_close();
    void display_issuccess(const QString&);
    void on_OK_clicked();
};

#endif // CHANGEPASSWORD_H
