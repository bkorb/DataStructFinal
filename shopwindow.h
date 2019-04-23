#ifndef SHOPWINDOW_H
#define SHOPWINDOW_H

#include <QMainWindow>
#include <string>
#include <QTableWidget>
#include <vector>
#include <queue>
#include "Inventory.hpp"
#include "returnscreen.h"

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

    void cuteReadCsvInventory(QString filename);

    void loadOptions();


    void on_addToButton_clicked();

    void on_sizeminCBox_currentIndexChanged(int index);

    void on_sizemaxCBox_currentIndexChanged(int index);

    void on_priceminCBox_currentIndexChanged(int index);

    void on_pricemaxCBox_currentIndexChanged(int index);

    void on_clearButton_clicked();

    void on_checkoutButton_clicked();

    void on_refreshButton_clicked();

    void on_fillButton_clicked();

    void on_serialButton_clicked();

    void on_returnSearchButton_clicked();

    void on_checkRepairs_stateChanged(int arg1);

    void on_nextSkiButton_clicked();

private:
    Inventory stock;
    vector<Element<Ski>*> currentSkiList;
    vector<Element<Ski>*> checkoutSkiList;
    queue<Element<Ski>*> returnSkiList;
    Ui::ShopWindow *ui;
    Element<Ski>** searchHelper(int &entries);
    Element<Ski>** searchAllHelper(int &entries);
    void returnHelper();
    void resetReturn();
    void queueHelper(PriorityQueue<Reservation> pq);
    void getDates(Date &begin, Date &end);
    bool inCart(Element<Ski> *ski);

    void clearHelper();
};

#endif // SHOPWINDOW_H
