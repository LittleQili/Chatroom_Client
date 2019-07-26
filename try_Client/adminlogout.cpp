#include "adminlogout.h"
#include "ui_adminlogout.h"

AdminLogout::AdminLogout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminLogout)
{
    ui->setupUi(this);
}

AdminLogout::~AdminLogout()
{
    delete ui;
}
