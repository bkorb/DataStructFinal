#include "shopwindow.h"
#include "ui_shopwindow.h"
#include "checkoutdialog.h"
#include <sstream>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

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
T *getParameterArray(QComboBox *mintable, QComboBox *maxtable, ArrayTable<T> &set, int &entries){
    entries = 0;//Number of choices the user gave
    int numOptions = 0;//Number of options for the user to choose from
    T *options = set.getQueries(numOptions);//Get a list of options for every type in a table.	for(int i = 0; i<numOptions; i++){
    int *choices = new int[mintable->count()];
//    if (mintable->currentIndex() <= 0)
//    {
//        entries = 0;
//        return nullptr;
//    }
    int idx = 0;
    for (int i = mintable->currentIndex(); i < maxtable->currentIndex()+1; i++)
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


    int *sizes = getAllArray(stock.sizes,numSizes);
    ui->sizeminCBox->clear();
    ui->sizemaxCBox->clear();
    for (int i = 0; i < numSizes; i++){
        ui->sizeminCBox->addItem(QString::number(sizes[i]));
        ui->sizemaxCBox->addItem(QString::number(sizes[i]+10));
    }
    int *prices = getAllArray(stock.prices,numPrices);
    ui->priceminCBox->clear();
    ui->pricemaxCBox->clear();
    for (int i = 0; i < numPrices; i++){
        ui->priceminCBox->addItem(QString::number(prices[i]));
        ui->pricemaxCBox->addItem(QString::number(prices[i]+10));
    }

//    ui->sizeMin->setText("0");
//        ui->sizeMax->setText("1000");
//        ui->priceMin->setText("0");
//        ui->priceMax->setText("1000");
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
    if (ui->checkSki->isChecked()){
        types[numTypes] = ski;
        numTypes++;
    }
    if (ui->checkSnowboard->isChecked()){
        types[numTypes] = snowboard;
        numTypes++;
    }

    int *sizes = getParameterArray(ui->sizeminCBox,ui->sizemaxCBox,stock.sizes,numSizes);
    int *prices = getParameterArray(ui->priceminCBox,ui->pricemaxCBox,stock.prices,numPrices);

    int syear, smonth, sday, eyear, emonth, eday;
        ui->dateStart->date().getDate(&syear, &smonth, &sday);
        ui->dateEnd->date().getDate(&eyear, &emonth, &eday);
        Date start(sday, smonth, syear);
        Date end(eday, emonth, eyear);

    return stock.searchUnits(brands,numBrands,models,numModels,types,numTypes,sizes,numSizes,prices,numPrices,start,end,entries);
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

    return stock.searchUnits(brands,numBrands,models,numModels,types,numTypes,sizes,numSizes,prices,numPrices,Date(),Date(),entries);
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
    QTableWidget *table = ui->tableWidget;
    table->clearContents();
    while (table->rowCount() > 0) table->removeRow(0);
    int entries = 0;
    while (!currentSkiList.empty()) currentSkiList.pop_back();

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
        currentSkiList.push_back(item);
        string type;
        if (item->data.type == ski) type = "Ski";
        else type = "Board";
        QStringList dataList;
        dataList << QString::fromStdString(type)
                 << QString::fromStdString(item->data.brand)
                 << QString::fromStdString(item->data.model)
                 << QString::number(item->data.size) + "cm"
                 << "$" + QString::number(item->data.price);

        //Expletive about Coding
        int syear, smonth, sday, eyear, emonth, eday;
            ui->dateStart->date().getDate(&syear, &smonth, &sday);
            ui->dateEnd->date().getDate(&eyear, &emonth, &eday);
            Date start(sday, smonth, syear);
            Date end(eday, emonth, eyear);


        table->insertRow(i);
        for (int j = 0; j < dataList.count(); j++){
        QTableWidgetItem *itm = new QTableWidgetItem;
        itm->setText(dataList[j]);
        if (inCart(item)) itm->setBackgroundColor(Qt::red);
        table->setItem(i,j,itm);
        }
    }
    ui->countLabel->setText(QString::number(entries));
}

void ShopWindow::on_openButton_clicked()
{
    clearHelper();
    QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),
                                                  "C://", "csv files (*.csv)");
    cuteReadCsvInventory(filename);
    loadOptions();
}

void ShopWindow::cuteReadCsvInventory(QString filename){
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

void ShopWindow::on_addToButton_clicked()
{
    if (ui->tableWidget->currentRow() >= 0){
    int row = ui->tableWidget->currentRow();
    Element<Ski> *ski = currentSkiList[row];
    if (!inCart(ski)){
            QTableWidget *itm = ui->tableWidget;
            QTableWidgetItem *nwItm = new QTableWidgetItem;
            QString title = itm->item(row,1)->text() + " " + itm->item(row,2)->text() + " " + itm->item(row,3)->text();
            nwItm->setText(title);
            QTableWidgetItem *nwItm2 = new QTableWidgetItem;
            nwItm2->setText("$" + QString::number(ski->data.price));

            ui->cartTable->insertRow(0);
            ui->cartTable->setItem(0,0,nwItm);
            ui->cartTable->setItem(0,1,nwItm2);

            checkoutSkiList.push_back(ski);
    }
    on_searchButton_clicked();
    }
}

void ShopWindow::getDates(Date &begin, Date &end){
    int syear,smonth,sday,eyear,emonth,eday;
    ui->dateStart->date().getDate(&syear,&smonth,&sday);
    ui->dateEnd->date().getDate(&eyear,&emonth,&eday);
    Date b(sday,smonth,syear);
    Date e(eday,emonth,eyear);
    begin = b;
    end = e;
}

bool ShopWindow::inCart(Element<Ski> *ski){
    bool inCart = false;
    for (int i = 0; i < checkoutSkiList.size(); i++){
        if (checkoutSkiList[i] == ski) inCart = true;
    }
    return inCart;
}

void ShopWindow::on_sizeminCBox_currentIndexChanged(int index)
{if (ui->sizemaxCBox->currentIndex() < index) ui->sizemaxCBox->setCurrentIndex(index);}
void ShopWindow::on_sizemaxCBox_currentIndexChanged(int index)
{if (ui->sizeminCBox->currentIndex() > index) ui->sizeminCBox->setCurrentIndex(index);}

void ShopWindow::on_priceminCBox_currentIndexChanged(int index)
{if (ui->pricemaxCBox->currentIndex() < index) ui->pricemaxCBox->setCurrentIndex(index);}
void ShopWindow::on_pricemaxCBox_currentIndexChanged(int index)
{if (ui->priceminCBox->currentIndex() > index) ui->priceminCBox->setCurrentIndex(index);}

void ShopWindow::on_clearButton_clicked()
{
    while (!checkoutSkiList.empty()) checkoutSkiList.pop_back();
    while (ui->cartTable->rowCount() > 0) ui->cartTable->removeRow(0);
    ui->groupTEdit->setText("");
    on_searchButton_clicked();
}

void ShopWindow::on_checkoutButton_clicked()
{
    if (ui->groupTEdit->text() == ""){
        checkoutDialog checkout;
        checkout.setModal(true);
        checkout.exec();
    }
    else{
    if (!checkoutSkiList.empty())
    {
//    checkoutDialog checkoutdialog;
//    checkoutdialog.setModal(true);
//    checkoutdialog.exec();
    Date begin, end;
    getDates(begin,end);
    int size = checkoutSkiList.size();
    Element<Ski> **units = new Element<Ski>*[checkoutSkiList.size()];
    for (int i = 0; i < checkoutSkiList.size(); i++){
        units[i] = checkoutSkiList[i];
    }
//    Element<Ski> **units = 0;
    string name = ui->groupTEdit->text().QString::toStdString();
    Reservation currOrder(units,size,begin,end,-1,100,name);
    currOrder.cost = rentalPrice(currOrder);
    stock.addToOrders(currOrder);
//    ui->orderTWidget->insertRow(0);
//    QTableWidgetItem *tmp = new QTableWidgetItem;
//    QTableWidgetItem *tmp2 = new QTableWidgetItem;
//    string resName = currOrder.groupName;
//    int resSize = currOrder.groupSize;
//    tmp->setText(QString::fromStdString(resName));
//    tmp2->setText(QString::number(resSize));
//    ui->orderTWidget->setItem(0,0,tmp);
//    ui->orderTWidget->setItem(0,1,tmp2);
    }

    on_searchButton_clicked();
    on_clearButton_clicked();
    on_refreshButton_clicked();
    }
}

void ShopWindow::on_refreshButton_clicked()
{
    QTableWidget *nxtTmp = ui->nextOut;
    if (!stock.orders.isEmpty()){
    string name = stock.orders.peek().groupName;
    int size = stock.orders.peek().groupSize;
    QTableWidgetItem *itm = new QTableWidgetItem;
    QTableWidgetItem *itm2 = new QTableWidgetItem;
    itm->setText(QString::fromStdString(name));
    itm2->setText(QString::number(size));
    nxtTmp->setItem(0,0,itm);
    nxtTmp->setItem(0,1,itm2);
    }
    else nxtTmp->clearContents();
}

//void ShopWindow::queueHelper(PriorityQueue<Reservation> pq){
    //while (ui->orderTWidget->rowCount() > 0) ui->orderTWidget->removeRow(0);
   // QTableWidget *table = ui->orderTWidget;
//    int i = 0;
//    while (i < 1)// && !pq.isEmpty())
//    {
//     QString groupname = QString::fromStdString(pq.peek().groupName);
//     int size = table->rowCount();
//     table->insertRow(0);

//    // QTableWidgetItem *itm = new QTableWidgetItem;
//    // itm->setText(groupname);
//    // table->setItem(size,0,itm);
//    i++;
//    pq.dequeue();
//    }
//}


void ShopWindow::on_fillButton_clicked()
{

    if (!stock.orders.isEmpty()){
    ui->orderTWidget->insertRow(0);
    QTableWidgetItem *tmp = new QTableWidgetItem;
    QTableWidgetItem *tmp2 = new QTableWidgetItem;
    string resName = stock.orders.peek().groupName;
    int resSize = stock.orders.peek().groupSize;
    tmp->setText(QString::fromStdString(resName));
    tmp2->setText(QString::number(resSize));
    ui->orderTWidget->setItem(0,0,tmp);
    ui->orderTWidget->setItem(0,1,tmp2);

    string name = stock.orders.peek().groupName;
    stock.groups.insert(name,stock.orders.peek());
    stock.orders.dequeue();
    }

    on_refreshButton_clicked();
}

void ShopWindow::on_serialButton_clicked()
{
    {
        clearHelper();
        QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),
                                                      "C://", "csv files (*.csv)");
        cuteReadInventory(filename);
        loadOptions();
    }
}

void ShopWindow::on_returnSearchButton_clicked()
{
    string name = ui->returnSearchLEdit->text().QString::toStdString();
    if (name != ""){
        int entries = 0;
        Reservation *res = stock.groups.search(name,entries);
        if (res != nullptr){
            for (int i = 0; i < res->groupSize; i++) returnSkiList.push(res->skis[i]);
            returnHelper();
//            ui->returnSearchButton->setEnabled(false);
//            for (int i = 0; i < res->groupSize; i++) returnSkiList.push(res->skis[i]);
//            string skiname = res->skis[0]->data.brand + res->skis[0]->data.model + " " + to_string(res->skis[0]->data.size) + "cm";
//            ui->skilabel->setText(QString::fromStdString(skiname));
//            ui->skitag->setEnabled(true);
//            ui->skilabel->setEnabled(true);
//            ui->nextSkiButton->setEnabled(true);
//            ui->checkRepairs->setEnabled(true);
        }
        else{
            checkoutDialog bad;
            bad.setModal(true);
            bad.exec();
        }
    }
}

void ShopWindow::on_checkRepairs_stateChanged(int arg1)
{
    if (arg1 > 0){
        ui->costLEdit->setEnabled(true);
        ui->costLabel->setEnabled(true);
    }
    else{
        ui->costLEdit->setEnabled(false);
        ui->costLabel->setEnabled(false);
    }
}

void ShopWindow::on_nextSkiButton_clicked()
{
    bool repairs = ui->checkRepairs->isChecked();
    int cost;
    int timestamp = 1;
    if (!repairs) cost = 0;
    else cost = ui->costLEdit->text().QString::toInt();

    ReturnItem ri(repairs,cost,timestamp);
    ri.ski = returnSkiList.front();
    stock.addToReturns(ri);
    returnSkiList.pop();
    if (!returnSkiList.empty()) returnHelper();
    else{
        ReturnScreen rs;
        rs.setModal(true);
        rs.exec();
        resetReturn();
    }
    ui->checkRepairs->setCheckState(Qt::CheckState(0));
    ui->costLEdit->setText("");
}

void ShopWindow::returnHelper(){
    ui->returnSearchButton->setEnabled(false);
    string skiname = returnSkiList.front()->data.brand + " " + returnSkiList.front()->data.model + " " + to_string(returnSkiList.front()->data.size) + "cm";
    ui->skilabel->setText(QString::fromStdString(skiname));
    ui->skitag->setEnabled(true);
    ui->skilabel->setEnabled(true);
    ui->nextSkiButton->setEnabled(true);
    ui->checkRepairs->setEnabled(true);
}

void ShopWindow::resetReturn(){
    ui->returnSearchButton->setEnabled(true);
    ui->skitag->setEnabled(false);
    ui->skilabel->setText("");
    ui->skilabel->setEnabled(false);
    ui->checkRepairs->setEnabled(false);
    ui->costLEdit->setEnabled(false);
    ui->costLabel->setEnabled(false);
    ui->returnSearchLEdit->setText("");
}
