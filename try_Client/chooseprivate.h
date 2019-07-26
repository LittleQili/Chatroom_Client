#ifndef CHOOSEPRIVATE_H
#define CHOOSEPRIVATE_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "mainwindow.h"

namespace Ui {
class ChoosePrivate;
}

class MainWindow;
class ChoosePrivate : public QDialog
{
    Q_OBJECT

public:
    explicit ChoosePrivate(MainWindow *xmw,QWidget *parent = 0);
    ~ChoosePrivate();

private:
    Ui::ChoosePrivate *ui;
    MainWindow *mw;
private slots:
    void confirm_private();
    void confirm_public();
};

#endif // CHOOSEPRIVATE_H
