#include <iostream>
#include <string>
#include "Inventory.hpp"

using namespace std;

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
	AbstractElement **pointers1 = found1->getPointers(entries);
	cout << "All faction units:" << endl;
	for(int i = 0; i<entries; i++){
		cout << ((Element<string>*)pointers1[i])->data << endl;
	}
	Element<string> search2("Line");
	Element<string> *found2 = brands.findElement(search2);
	AbstractElement **pointers2 = found2->getPointers(entries);
	cout << "All line units:" << endl;
	for(int i = 0; i<entries; i++){
		cout << ((Element<string>*)pointers2[i])->data << endl;
	}
	Element<string> search3("Armada");
	Element<string> *found3 = brands.findElement(search3);
	AbstractElement **pointers3 = found3->getPointers(entries);
	cout << "All armada units:" << endl;
	for(int i = 0; i<entries; i++){
		cout << ((Element<string>*)pointers3[i])->data << endl;
	}

	Inventory inventory;

	cout << "Done" << endl;

	return 0;
}