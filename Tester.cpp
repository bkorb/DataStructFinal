#include <iostream>
#include <string>
#include "Database.hpp"

using namespace std;

enum Type {ski, snowboard};

class Ski{
private:
	int cost;
	int repairs;
	int costOfRepairs;
public:
	Ski(int cost);
};

class Inventory{
private:
	ArrayTable<string> brands;
	ArrayTable<string> models;
	ArrayTable<Type> types;
	ArrayTable<int> sizes;
	ArrayTable<int> prices;
	ListTable<Ski> units;
public:
	Inventory();
	~Inventory();
	void addUnit(string brand, string model, Type type, int size, int price);
	Element<Ski> **searchUnits(string *brands, string *models, Type *types, int *sizes, int *prices);
	void removeUnit(Element<Ski> *unit);
}

int main(){
	cout << "start" << endl;
	ArrayTable<string> brands("Brands");
	ListTable<string> units("Units");

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

	return 0;
}