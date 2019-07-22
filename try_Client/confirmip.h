#ifndef CONFIRMIP_H
#define CONFIRMIP_H

#include <QDialog>

namespace Ui {
class ConfirmIP;
}

class ConfirmIP : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmIP(QWidget *parent = 0);
    ~ConfirmIP();

private:
    Ui::ConfirmIP *ui;
};

#endif // CONFIRMIP_H
