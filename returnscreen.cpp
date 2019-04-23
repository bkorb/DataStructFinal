#include "returnscreen.h"
#include "ui_returnscreen.h"

ReturnScreen::ReturnScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReturnScreen)
{
    ui->setupUi(this);
}

ReturnScreen::~ReturnScreen()
{
    delete ui;
}

void ReturnScreen::on_ReturnOk_clicked()
{
    close();
}
