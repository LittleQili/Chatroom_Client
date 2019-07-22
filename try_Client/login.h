#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "register.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_Register_clicked();

private:
    Ui::Login *ui;
    chatClient *cl;
};

#endif // LOGIN_H
