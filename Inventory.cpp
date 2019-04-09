#include <iostream>
#include <string>
#include "Inventory.hpp"

using namespace std;

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

Ski::Ski(){
	brand = "";
	model = "";
	type = null;
	size = NULL;
	price = NULL;
	cost = NULL;
	repairs = NULL;
	costOfRepairs = NULL;
}

void Inventory::addUnit(string brand, string model, Type type, int size, int price, int cost){
	Ski ski(brand, model, type, size, price, cost);
	ListElement<Ski> *unit = new ListElement<Ski>(ski);
	units.addElement(unit);

	Element<string> E_brand(brand);
	Element<string> *foundS = brands.findElement(E_brand);
	if(foundS!=nullptr){
		foundS = brands.addElement(E_brand);
	}
	foundS->addPointer(unit);

	Element<string> E_model(model);
	foundS = models.findElement(E_model);
	if(foundS!=nullptr){
		foundS = models.addElement(E_model);
	}
	foundS->addPointer(unit);

	Element<Type> E_type(type);
	Element<Type> *foundT = types.findElement(E_type);
	if(foundT!=nullptr){
		foundT = types.addElement(E_type);
	}
	foundT->addPointer(unit);

	Element<int> E_size(size);
	Element<int> *foundI = sizes.findElement(E_size);
	if(foundI!=nullptr){
		foundI = sizes.addElement(E_size);
	}
	foundI->addPointer(unit);

	Element<int> E_price((price/10)*10);
	foundI = sizes.findElement(E_price);
	if(foundI!=nullptr){
		foundI = prices.addElement(E_price);
	}
	foundI->addPointer(unit);
}

Element<Ski> **Inventory::searchUnits(string *brands, string *models, Type *types, int *sizes, int *prices){
	AbstractElement **units = new AbstractElement*[1];
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