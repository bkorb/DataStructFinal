#include <iostream>
#include <string>
#include "Database.hpp"

using namespace std;

enum Type {ski, snowboard};

class Ski{
private:
	string brand;
	string model;
	Type type;
	int size;
	int price;
	int cost;
	int repairs;
	int costOfRepairs;
public:
	Ski(string _brand, string _model, Type _type, int _size, int _price, int _cost);
};

Ski::Ski(string _brand, string _model, Type _type, int _size, int _price, int _cost){
	brand = _brand;
	model = _model;
	type = _type;
	size = _size;
	price = _price;
	cost = _cost;
	repairs = 0;
	costOfRepairs = 0;
}

class Inventory{
private:
	ArrayTable<string> brands;
	ArrayTable<string> models;
	ArrayTable<Type> types;
	ArrayTable<int> sizes;
	ArrayTable<int> prices;
	ListTable<Ski> units;
public:
	void addUnit(string brand, string model, Type type, int size, int price, int cost);
	Element<Ski> **searchUnits(string *brands, string *models, Type *types, int *sizes, int *prices);
	void removeUnit(Element<Ski> *unit);
};

void Inventory::addUnit(string brand, string model, Type type, int size, int price, int cost){
	Ski ski(brand, model, type, size, price, cost);
	Element<Ski> *unit = new ListElement<ski>(ski);
	units.addElement(unit);

	Element<string> E_brand(brand);
	Element<string> foundS = findElement(E_brand);
	if(!foundS){
		foundS = brands.addElement(E_brand);
	}
	foundS.addPointer(unit);

	Element<string> E_model(model);
	foundS = models.findElement(E_model);
	if(!foundS){
		foundS = models.addElement(E_model);
	}
	foundS.addPointer(unit);

	Element<Type> E_type(type);
	Element<Type> foundT = types.findElement(E_type);
	if(!foundT){
		foundT = types.addElement(E_type);
	}
	foundT.addPointer(unit);

	Element<int> E_size(size);
	Element<int> foundI = sizes.findElement(E_size);
	if(!foundI){
		foundI = sizes.addElement(E_size);
	}
	foundI.addPointer(unit);

	Element<int> E_price(price);
	foundI = sizes.findElement(E_price);
	if(!foundI){
		foundI = prices.addElement(E_price);
	}
	foundI.addPointer(unit);
}

Element<Ski> **searchUnits(string *brands, string *models, Type *types, int *sizes, int *prices){
	if(brands){

	}
	if(models){

	}
	if(types){

	}
	if(sizes){

	}
	if(prices){

	}
}


int main(){
	cout << "start" << endl;
	ArrayTable<string> brands;
	ListTable<string> units;

	Element<string> faction("Faction");
	brands.addElement(faction);

	Element<string> armada("Armada");
	brands.addElement(armada);

	Element<string> line("Line");
	brands.addElement(line);

	Element<string> *factionp = brands.findElement(faction);
	Element<string> *linep = brands.findElement(line);
	Element<string> *armadap = brands.findElement(armada);

	ListElement<string> *candide = new ListElement<string>("Candide");
	units.addElement(candide);
	factionp->addPointer(candide);
	candide->addPointer(factionp);

	ListElement<string> *wallisch = new ListElement<string>("Tom Wallisch Pro");
	units.addElement(wallisch);
	linep->addPointer(wallisch);
	wallisch->addPointer(linep);

	ListElement<string> *dictator = new ListElement<string>("Dictator");
	units.addElement(dictator);
	factionp->addPointer(dictator);
	dictator->addPointer(factionp);

	int entries;
	Element<string> search1("Faction");
	Element<string> *found1 = brands.findElement(search1);
	Element<string> **pointers1 = found1->getPointers(entries);
	cout << "All faction units:" << endl;
	for(int i = 0; i<entries; i++){
		cout << pointers1[i]->data << endl;
	}
	Element<string> search2("Line");
	Element<string> *found2 = brands.findElement(search2);
	Element<string> **pointers2 = found2->getPointers(entries);
	cout << "All line units:" << endl;
	for(int i = 0; i<entries; i++){
		cout << pointers2[i]->data << endl;
	}
	Element<string> search3("Armada");
	Element<string> *found3 = brands.findElement(search3);
	Element<string> **pointers3 = found3->getPointers(entries);
	cout << "All armada units:" << endl;
	for(int i = 0; i<entries; i++){
		cout << pointers3[i]->data << endl;
	}

	Inventory inventory;

	return 0;
}