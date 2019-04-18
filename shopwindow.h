#ifndef SHOPWINDOW_H
#define SHOPWINDOW_H

#include <QMainWindow>
#include <string>
#include "Inventory.hpp"

namespace Ui {
class ShopWindow;
}

class ShopWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShopWindow(QWidget *parent = nullptr);
    ~ShopWindow();



private slots:
    void on_searchButton_clicked();

    void on_openButton_clicked();

    void cuteReadInventory(QString filename);

    void loadOptions();

private:
    Inventory stock;
    Ui::ShopWindow *ui;
    Element<Ski>** searchHelper(int &entries);
};

#endif // SHOPWINDOW_H
