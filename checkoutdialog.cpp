#include "checkoutdialog.h"
#include "ui_checkoutdialog.h"

checkoutDialog::checkoutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkoutDialog)
{
    ui->setupUi(this);
    ui->outTWidget->insertRow(0);
    QTableWidgetItem *itm = new QTableWidgetItem;
    itm->setText("place");
    ui->outTWidget->setItem(0,0,itm);
}

checkoutDialog::~checkoutDialog()
{
    delete ui;
}
