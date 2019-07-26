#ifndef ADMINCHOOSE_H
#define ADMINCHOOSE_H

#include <QDialog>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDebug>
#include "client.h"
#include "mainwindow.h"

namespace Ui {
class AdminChoose;
}
class MainWindow;
class AdminChoose : public QDialog
{
    Q_OBJECT

public:
    explicit AdminChoose(QString xtype,QString x_IP, uint16_t x_port, QString xname,QWidget *parent = 0);
    ~AdminChoose();

private:
    Ui::AdminChoose *ui;
    chatClient *cl;
    QString name;
    QString con_IP;
    uint16_t con_port;

    bool isconnected;
    QString next_name;
    QString type;
    /*type 有以下几种：
     * logout
     * quiry
     * change
     * forbid
     *
     */
//    MainWindow* mw;
private slots:
    void readmsg(const QString&);
    void on_OK_clicked();
};

#endif // ADMINCHOOSE_H
