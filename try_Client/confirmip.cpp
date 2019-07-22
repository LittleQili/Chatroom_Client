#include "confirmip.h"
#include "ui_confirmip.h"

ConfirmIP::ConfirmIP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmIP)
{
    ui->setupUi(this);
}

ConfirmIP::~ConfirmIP()
{
    delete ui;
}
