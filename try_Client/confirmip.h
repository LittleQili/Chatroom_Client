#ifndef CONFIRMIP_H
#define CONFIRMIP_H

#include "login.h"

namespace Ui {
class ConfirmIP;
}

class ConfirmIP : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmIP(QWidget *parent = 0);
    ~ConfirmIP();

private slots:
    void on_OK_clicked();
    void display_isconnected(const QString&);
private:
    Ui::ConfirmIP *ui;
    chatClient *cl;
    QString con_IP;
    uint16_t con_port;
private:
    void RunClientProcess();
};

#endif // CONFIRMIP_H
