#include "shopwindow.h"
#include "ui_shopwindow.h"
#include <sstream>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

template <class T>
T  *getAllArray(ArrayTable<T> &set, int &entries){
    entries = 0;
    int numOptions = 0;
    T *options = set.getQueries(numOptions);
    entries = numOptions;
    return options;
}

template <class T>
T *getParameterArray(QListWidget *table, ArrayTable<T> &set, int &entries){
    entries = 0;//Number of choices the user gave
    int numOptions = 0;//Number of options for the user to choose from
    T *options = set.getQueries(numOptions);//Get a list of options for every type in a table.	for(int i = 0; i<numOptions; i++){
    int *choices = new int[table->count()];
    int idx = 0;
    for (int i = 0; i < table->count(); i++){
        choices[idx] = -1;
        if (table->item(i)->isSelected()){
            entries++;
            choices[idx] = i;
            idx++;
        }
    }
    if(choices[0] == -1){//If you want to choose every option
        entries = 0;//If entries is 0 and parameters is a nullptr the searchUnits function will return all of that type
        return nullptr;
    }
    int num = choices[0];
    T *parameters = new T[entries];
    int index = 0;
    while(index < entries && num != -1){//Streaming in each choice that the user input.
        parameters[index] = options[choices[index]];
        index++;
        num = choices[index];
    }
    return parameters;
}

//TODO Fix a segmentation fault.
template <class T>
T *getParameterArray(QComboBox *table, ArrayTable<T> &set, int &entries){
    entries = 0;//Number of choices the user gave
    int numOptions = 0;//Number of options for the user to choose from
    T *options = set.getQueries(numOptions);//Get a list of options for every type in a table.	for(int i = 0; i<numOptions; i++){
    int *choices = new int[table->count()];
    if (table->currentIndex() <= 0)
    {
        entries = 0;
        return nullptr;
    }
    int idx = 0;
    for (int i = table->currentIndex() - 1; i < table->count(); i++)
    {
        choices[idx] = i;
        entries++;
        idx++;
    }

    int num = choices[0];
    T *parameters = new T[entries];
    int index = 0;
    while(index < entries && num != -1)
    {
        parameters[index] = options[choices[index]];
        index++;
        num = choices[index];
    }
    return parameters;
}

ShopWindow::ShopWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShopWindow)
{
    ui->setupUi(this);
     ui->tableWidget->clear();

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
    string *brands = getAllArray<string>(stock.brands,numBrands);
    ui->brandLWidget->clear();
    for (int i = 0; i < numBrands; i++){
        QString str = QString::fromStdString(brands[i]);
        ui->brandLWidget->addItem(str);
    }
    string *models = getAllArray<string>(stock.models,numModels);
    ui->modelLWidget->clear();
    for (int i = 0; i < numModels; i++){
        QString str = QString::fromStdString(models[i]);
        ui->modelLWidget->addItem(str);
    }

    ui->sizeMin->setText("0");
    ui->sizeMax->setText("1000");
    ui->priceMin->setText("0");
    ui->priceMax->setText("1000");
}

Element<Ski>** ShopWindow::searchHelper(int &entries)
{
    int numBrands, numModels, numTypes, numSizes, numPrices;
    numSizes =0;
    numPrices = 0;
    string *brands = getParameterArray<string>(ui->brandLWidget,stock.brands,numBrands);
    string *models = getParameterArray<string>(ui->modelLWidget,stock.models,numModels);

    //Type *types = getParameterArray(ui->typeLWidget,stock.types,numTypes);
    numTypes = 0;
    Type *types = new Type[2];
    if(ui->checkSki->isChecked()){
        types[numTypes] = ski;
        numTypes++;
    }
    if(ui->checkSnowboard->isChecked()){
        types[numTypes] = snowboard;
        numTypes++;
    }

    numSizes = 0;
    int numSizeOptions;
    int *allsizes = getAllArray(stock.sizes,numSizeOptions);
    int sizemin = stoi(ui->sizeMin->toPlainText().toStdString());
    int sizemax = stoi(ui->sizeMax->toPlainText().toStdString());
    int *sizes = new int[numSizeOptions];
    if(ui->sizeMin->toPlainText()!="" && ui->sizeMin->toPlainText()!=""){
        for(int i = 0; i<numSizeOptions; i++){
            if(allsizes[i]>sizemin && allsizes[i]<sizemax){
                sizes[numSizes] = allsizes[i];
                numSizes++;
            }
        }
        if(numSizes == 0){
            entries = 0;
            return nullptr;
        }
    }else{
        numSizes = 0;
    }

    numPrices = 0;
    int numPriceOptions;
    int *allprices = getAllArray(stock.prices,numPriceOptions);
    int pricemin = stoi(ui->priceMin->toPlainText().toStdString());
    int pricemax = stoi(ui->priceMax->toPlainText().toStdString());
    int *prices = new int[numPriceOptions];
    if(ui->priceMin->toPlainText()!="" && ui->priceMin->toPlainText()!=""){
        for(int i = 0; i<numPriceOptions; i++){
            if(allprices[i]>=pricemin && allprices[i]<pricemax){
                prices[numPrices] = allprices[i];
                numPrices++;
            }
        }
        if(numPrices == 0){
            entries = 0;
            return nullptr;
        }
    }else{
        numPrices = 0;
    }

    int syear, smonth, sday, eyear, emonth, eday;
    ui->dateStart->date().getDate(&syear, &smonth, &sday);
    ui->dateEnd->date().getDate(&eyear, &emonth, &eday);
    Date start(sday, smonth, syear);
    Date end(eday, emonth, eyear);

    return stock.searchUnits(brands,numBrands,models,numModels,types,numTypes,sizes,numSizes,prices,numPrices,start, end, entries);
}

Element<Ski>** ShopWindow::searchAllHelper(int &entries)
{
    int numBrands, numModels, numTypes, numSizes, numPrices;
    numBrands = numModels = numTypes = numSizes = numPrices = 0;
    string *brands = nullptr;//getParameterArray<string>(stock.brands,numBrands,choices);
    string *models = nullptr;//getParameterArray<string>(stock.models,numModels,choices);
    Type *types = nullptr;//getParameterArray(stock.types,numTypes,choices);
    int *sizes = nullptr;//getParameterArray(stock.sizes,numSizes,choices);
    int *prices = nullptr;//getParameterArray(stock.prices,numPrices,choices);

    return stock.searchUnits(brands,numBrands,models,numModels,types,numTypes,sizes,numSizes,prices,numPrices,Date(), Date(), entries);
}

void ShopWindow::clearHelper(){
   int entries = 0;
   Element<Ski> **units = searchAllHelper(entries);
   for (int i = 0; i < entries; i++){
       stock.removeUnit(units[i]);
   }
}

void ShopWindow::on_searchButton_clicked()
{
    ui->tableWidget->clear();
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
            sortBySize(units,0,entries-1);
        break;
    default:
        break;
    }
    for (int i = 0; i < entries; i++){
        Element<Ski> *item = units[i];
        string type;
        if (item->data.type == ski) type = "Ski";
        else type = "Board";
        QStringList dataList;
        dataList << QString::fromStdString(type)
                 << QString::fromStdString(item->data.brand)
                 << QString::fromStdString(item->data.model)
                 << QString::number(item->data.size) + "cm"
                 << "$" + QString::number(item->data.price);
        ui->tableWidget->insertRow(i);
        for (int j = 0; j < dataList.count(); j++){
        QTableWidgetItem *itm = new QTableWidgetItem;
        itm->setText(dataList[j]);
        ui->tableWidget->setItem(i,j,itm);
        }
    }
    ui->countLabel->setText(QString::number(entries));
}

void ShopWindow::on_openButton_clicked()
{
    clearHelper();
    QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),
                                                  "C://", "csv files (*.csv)");
    cuteReadInventory(filename);
    loadOptions();
}

void ShopWindow::cuteReadInventory(QString filename){
    stringstream ss;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
     QTextStream in(&file);
     while (!in.atEnd())
     {
      QString line = in.readLine();
      ss << line.toStdString() << endl;
     }
    }
    stock.loadFromFile(ss);
}
