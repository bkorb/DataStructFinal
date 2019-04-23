#ifndef RETURNSCREEN_H
#define RETURNSCREEN_H

#include <QDialog>

namespace Ui {
class ReturnScreen;
}

class ReturnScreen : public QDialog
{
    Q_OBJECT

public:
    explicit ReturnScreen(QWidget *parent = nullptr);
    ~ReturnScreen();

private slots:
    void on_ReturnOk_clicked();

private:
    Ui::ReturnScreen *ui;
};

#endif // RETURNSCREEN_H
