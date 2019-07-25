#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QScrollBar>
#include "client.h"
#include "changename.h"
#include "changepassword.h"

namespace Ui {
class MainWindow;
}
class ChangeName;
class ChangePassword;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString x_IP, uint16_t x_port,QString xname,QWidget *parent = nullptr);
    ~MainWindow();
    void name_changed(const QString&);

private:
    Ui::MainWindow *ui;
    chatClient *cl;
    QString name;
    QString con_IP;
    uint16_t con_port;

signals:
    void newMessageSent(const QString &);

private slots:
    void on_send_button_clicked();
    void on_actionLog_out_triggered();
    void add_new_msg(const QString&);
    void on_actionChange_your_name_triggered();
    void on_actionChange_your_password_triggered();
};

#endif // MAINWINDOW_H
