#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString x_IP, uint16_t x_port,QString xname,QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    chatClient *cl;
    QString name;
signals:
    void newMessageSent(const QString &);

private slots:
    void on_send_button_clicked();
    void add_new_msg(const QString&);
};

#endif // MAINWINDOW_H
