#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDebug>
#include "client.h"

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

private slots:
    void on_Confirm_clicked();

    void on_Return_clicked();

private:
    Ui::Register *ui;
    chatClient *cl;
};

#endif // REGISTER_H
