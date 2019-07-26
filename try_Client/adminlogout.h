#ifndef ADMINLOGOUT_H
#define ADMINLOGOUT_H

#include <QDialog>

namespace Ui {
class AdminLogout;
}

class AdminLogout : public QDialog
{
    Q_OBJECT

public:
    explicit AdminLogout(QWidget *parent = 0);
    ~AdminLogout();

private:
    Ui::AdminLogout *ui;
};

#endif // ADMINLOGOUT_H
