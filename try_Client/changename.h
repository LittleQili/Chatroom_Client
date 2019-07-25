#ifndef CHANGENAME_H
#define CHANGENAME_H

#include <QDialog>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDebug>
#include "client.h"
#include "mainwindow.h"

namespace Ui {
class ChangeName;
}

class MainWindow;
class ChangeName : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeName(QString x_IP, uint16_t x_port,QString xname,MainWindow *mw,QWidget *parent = 0);
    ~ChangeName();

signals:
    void nameChanged(const QString&);
private:
    Ui::ChangeName *ui;
    chatClient *cl;
    QString name;
    QString con_IP;
    uint16_t con_port;

    bool isconnected;
    QString newname;
    MainWindow* mw;
private slots:
    void quit_and_close();
    void display_issuccess(const QString&);

    void on_Ok_clicked();
};

#endif // CHANGENAME_H
