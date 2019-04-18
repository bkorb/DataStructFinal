#include "shopwindow.h"
#include "ui_shopwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

template <class T>
T *getParameterArray(ArrayTable<T> &set, int &entries){
    entries = 0;
    int numOptions = 0;
    T *options = set.getQueries(numOptions);
    entries = numOptions;
    return options;
}

ShopWindow::ShopWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopWindow)
{
    ui->setupUi(this);
     ui->sizeCBox->addItem("Select...");
     ui->priceCBox->addItem("Select...");

     ui->sortCBox->addItem("Price");
     ui->sortCBox->addItem("Brand");
     ui->sortCBox->addItem("Model");
     ui->sortCBox->addItem("Type");
     ui->sortCBox->addItem("Size");

}

ShopWindow::~ShopWindow()
{
    delete ui;
}

void ShopWindow::loadOptions(){
    int numBrands,numModels,numSizes,numPrices;
    string *brands = getParameterArray<string>(stock.brands,numBrands);
    for (int i = 0; i < numBrands; i++){
        QString str = QString::fromStdString(brands[i]);
        ui->brandLWidget->addItem(str);
    }
    string *models = getParameterArray<string>(stock.models,numModels);
    for (int i = 0; i < numModels; i++){
        QString str = QString::fromStdString(models[i]);
        ui->modelLWidget->addItem(str);
    }
        ui->typeLWidget->addItem("Ski");
        ui->typeLWidget->addItem("Snowboard");
    int *sizes = getParameterArray(stock.sizes,numSizes);
    for (int i = 0; i < numSizes; i++){
        ui->sizeCBox->addItem(QString::number(sizes[i]));
    }
    int *prices = getParameterArray(stock.prices,numPrices);
    for (int i = 0; i < numPrices; i++){
        ui->priceCBox->addItem(QString::number(prices[i]));
    }
}

Element<Ski>** ShopWindow::searchHelper(int &entries)
{
    int numBrands, numModels, numTypes, numSizes, numPrices;
    numBrands = numModels = numTypes = numSizes = numPrices = 0;
    string *brands = nullptr;//getParameterArray<string>(stock.brands,numBrands);
    string *models = nullptr;//getParameterArray<string>(stock.models,numModels);
    Type *types = nullptr;//getParameterArray(stock.types,numTypes);
    int *sizes = nullptr;//getParameterArray(stock.sizes,numSizes);
    int *prices = nullptr;//getParameterArray(stock.sizes,numPrices);

    return stock.searchUnits(brands,numBrands,models,numModels,types,numTypes,sizes,numSizes,prices,numPrices,entries);
}


void ShopWindow::on_searchButton_clicked()
{
    ui->listWidget->clear();
    int entries = 0;
    Element<Ski> **units = searchHelper(entries);
    int sortIndex = ui->sortCBox->currentIndex();
    switch (sortIndex){
        case 0:
            sortByPrice(units,0,entries-1);
        break;
        case 1:
            sortByBrand(units,0,entries-1);
        break;
        case 2:
            sortByModel(units,0,entries-1);
        break;
        case 3:
            sortByType(units,0,entries-1);
        break;
        case 4:
            sortByPrice(units,0,entries-1);
        break;
    default:
        break;
    }
    for (int i = 0; i < entries; i++){
        Element<Ski> *item = units[i];
        string type;
        if (item->data.type == ski) type = "Ski";
        else type = "Board";
        string info = item->data.brand + " | " + type + " | " + item->data.model + " | " + to_string(item->data.size) + "cm | $" + to_string(item->data.price);
        ui->listWidget->addItem(QString::fromStdString(info));
    }
    ui->countLabel->setText(QString::number(entries));
}

void ShopWindow::on_openButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),
                                                  "C://", "csv files (*.csv)");
    cuteReadInventory(filename);
    loadOptions();
}

void ShopWindow::cuteReadInventory(QString filename){
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
     QTextStream in(&file);
     while (!in.atEnd())
     {
      QString line = in.readLine();
      QStringList row = line.split(',',QString::SkipEmptyParts);
      string brand,model,typestring,sizestring,pricestring;
      int size,price;
      Type type;
      brand = row[0].toStdString();
      model = row[1].toStdString();
      if (row[2] == "ski") type = ski;
      else type = snowboard;
      size = row[3].toInt();
      price = row[4].toInt();

      stock.addUnit(brand,model,type,size,price,0);
     }
    }
}
