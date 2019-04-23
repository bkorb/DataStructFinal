#ifndef CHECKOUTDIALOG_H
#define CHECKOUTDIALOG_H

#include <QDialog>

namespace Ui {
class checkoutDialog;
}

class checkoutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit checkoutDialog(QWidget *parent = nullptr);
    ~checkoutDialog();



private:
    Ui::checkoutDialog *ui;
};

#endif // CHECKOUTDIALOG_H
