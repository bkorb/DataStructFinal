#include "checkoutdialog.h"
#include "ui_checkoutdialog.h"

checkoutDialog::checkoutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkoutDialog)
{
    ui->setupUi(this);
}

checkoutDialog::~checkoutDialog()
{
    delete ui;
}

void checkoutDialog::on_pushButton_clicked()
{
    close();
}
