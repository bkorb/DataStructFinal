#include "shopwindow.h"
#include <iostream>
#include <QApplication>
#include <QFile>
#include <QStringList>

using namespace std;
/*
void cuteReadInventory(Inventory &inventory){
    QFile file("");
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

      inventory.addUnit(brand,model,type,size,price,0);
     }
    }
}

*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShopWindow w;
    w.show();

    return a.exec();
}
