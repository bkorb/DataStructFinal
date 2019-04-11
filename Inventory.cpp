#include <iostream>
#include <string>
#include "Inventory.hpp"

using namespace std;

//Ski class main constructor
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

Ski::Ski(const Ski &old){
	brand = old.brand;
	model = old.model;
	type = old.type;
	size = old.size;
	price = old.price;
	cost = old.cost;
	repairs = old.repairs;
	costOfRepairs = old.costOfRepairs;
}

//Ski class default constructor
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

Ski::~Ski(){
}

ostream & operator<<(ostream &Str, const Ski &v) { 
  Str << "Ski: " << v.brand << ", " << v.model << ", " << v.type << ", " << v.size << ", " << v.price;
  return Str;
}

//Function to add a new unit to the inventory
void Inventory::addUnit(string brand, string model, Type type, int size, int price, int cost){
	Ski ski(brand, model, type, size, price, cost);
	//cout << "Adding " << ski << endl;
	ListElement<Ski> *unit = new ListElement<Ski>(ski);
	units.addElement(unit);

	Element<string> *foundBrand = brands.addElement(Element<string>(brand));
	foundBrand->addPointer(unit);
	unit->addPointer(foundBrand);

	Element<string> *foundModel = models.addElement(Element<string>(model));
	foundModel->addPointer(unit);
	unit->addPointer(foundModel);

	Element<Type> *foundType = types.addElement(Element<Type>(type));
	foundType->addPointer(unit);
	unit->addPointer(foundType);

	Element<int> *foundSize = sizes.addElement(Element<int>((size/10)*10));
	foundSize->addPointer(unit);
	unit->addPointer(foundSize);

	Element<int> *foundPrice = prices.addElement(Element<int>((price/10)*10));
	foundPrice->addPointer(unit);
	unit->addPointer(foundPrice);
}

//Funciton to query inventory for any combination of parameters and
//return all units that match
//TODO: speed up array combining
Element<Ski> **Inventory::searchUnits(string *brandList, int numBrands, string *modelList, int numModels, Type *typeList, int numTypes, int *sizeList, int numSizes, int *priceList, int numPrices, int &entries){
	AbstractElement **allunits = new AbstractElement*[1];
	int allsize = 1;
	int allelements = 0;

	AbstractElement **brandunits = new AbstractElement*[1];
	int brandsize = 1;
	int brandelements = 0;
	for(int i = 0; i<numBrands; i++){
		Element<string> brand(brandList[i]);
		Element<string> *brandp = brands.findElement(brand);
		if(brandp!=nullptr){
			int entries = 0;
			AbstractElement **pointers = brandp->getPointers(entries);
			for(int j = 0; j<entries; j++){
				if(brandsize==brandelements){
					doublePointerArray(brandunits, brandsize, brandelements);
				}
				if(allsize==allelements){
					doublePointerArray(allunits, allsize, allelements);
				}
				insertIntoPointerArray(allunits, allsize, allelements, pointers[j]);
				insertIntoPointerArray(brandunits, brandsize, brandelements, pointers[j]);
			}
		}
	}
	AbstractElement **modelunits = new AbstractElement*[1];
	int modelsize = 1;
	int modelelements = 0;
	for(int i = 0; i<numModels; i++){
		Element<string> model(modelList[i]);
		Element<string> *modelp = models.findElement(model);
		if(modelp!=nullptr){
			int entries = 0;
			AbstractElement **pointers = modelp->getPointers(entries);
			for(int j = 0; j<entries; j++){
				if(modelsize==modelelements){
					doublePointerArray(modelunits, modelsize, modelelements);
				}
				if(allsize==allelements){
					doublePointerArray(allunits, allsize, allelements);
				}
				insertIntoPointerArray(allunits, allsize, allelements, pointers[j]);
				insertIntoPointerArray(modelunits, modelsize, modelelements, pointers[j]);
			}
		}
	}
	AbstractElement **typeunits = new AbstractElement*[1];
	int typesize = 1;
	int typeelements = 0;
	for(int i = 0; i<numTypes; i++){
		Element<Type> type(typeList[i]);
		Element<Type> *typep = types.findElement(type);
		if(typep!=nullptr){
			int entries = 0;
			AbstractElement **pointers = typep->getPointers(entries);
			for(int j = 0; j<entries; j++){
				if(typesize==typeelements){
					doublePointerArray(typeunits, typesize, typeelements);
				}
				if(allsize==allelements){
					doublePointerArray(allunits, allsize, allelements);
				}
				insertIntoPointerArray(allunits, allsize, allelements, pointers[j]);
				insertIntoPointerArray(typeunits, typesize, typeelements, pointers[j]);
			}
		}
	}
	AbstractElement **sizeunits = new AbstractElement*[1];
	int sizesize = 1;
	int sizeelements = 0;
	for(int i = 0; i<numSizes; i++){
		Element<int> size((sizeList[i]/10)*10);
		Element<int> *sizep = sizes.findElement(size);
		if(sizep!=nullptr){
			int entries = 0;
			AbstractElement **pointers = sizep->getPointers(entries);
			for(int j = 0; j<entries; j++){
				if(sizesize==sizeelements){
					doublePointerArray(sizeunits, sizesize, sizeelements);
				}
				if(allsize==allelements){
					doublePointerArray(allunits, allsize, allelements);
				}
				insertIntoPointerArray(allunits, allsize, allelements, pointers[j]);
				insertIntoPointerArray(sizeunits, sizesize, sizeelements, pointers[j]);
			}
		}
	}
	AbstractElement **priceunits = new AbstractElement*[1];
	int pricesize = 1;
	int priceelements = 0;
	for(int i = 0; i<numPrices; i++){
		Element<int> price((priceList[i]/10)*10);
		Element<int> *pricep = prices.findElement(price);
		if(pricep!=nullptr){
			int entries = 0;
			AbstractElement **pointers = pricep->getPointers(entries);
			for(int j = 0; j<entries; j++){
				if(pricesize==priceelements){
					doublePointerArray(priceunits, pricesize, priceelements);
				}
				if(allsize==allelements){
					doublePointerArray(allunits, allsize, allelements);
				}
				insertIntoPointerArray(allunits, allsize, allelements, pointers[j]);
				insertIntoPointerArray(priceunits, pricesize, priceelements, pointers[j]);
			}
		}
	}

	int brandindex = 0;
	int modelindex = 0;
	int typeindex = 0;
	int sizeindex = 0;
	int priceindex = 0;

	AbstractElement **units = new AbstractElement*[1];
	int size = 1;
	int elements = 0;

	for(int i = 0; i<allelements; i++){
		bool keep = true;
		if(brandunits[brandindex]==allunits[i]){
			brandindex++;
		}else{
			if(numBrands>0) keep = false;
		}
		if(modelunits[modelindex]==allunits[i]){
			modelindex++;
		}else{
			if(numModels>0) keep = false;
		}
		if(typeunits[typeindex]==allunits[i]){
			typeindex++;
		}else{
			if(numTypes>0) keep = false;
		}
		if(sizeunits[sizeindex]==allunits[i]){
			sizeindex++;
		}else{
			if(numSizes>0) keep = false;
		}
		if(priceunits[priceindex]==allunits[i]){
			priceindex++;
		}else{
			if(numPrices>0) keep = false;
		}
		if(keep){
			if(size==elements){
				doublePointerArray(units, size, elements);
			}
			insertIntoPointerArray(units, size, elements, allunits[i]);
		}
	}
	entries = elements;
	Element<Ski> **skiunits = new Element<Ski>*[elements];
	for(int i = 0; i<elements; i++){
		skiunits[i] = (Element<Ski>*)units[i];
	}
	return skiunits;
}

void Inventory::removeUnit(Element<Ski> *unit){
	ListElement<Ski> *listunit = (ListElement<Ski> *)unit;
	units.deleteElement(listunit);

	Element<string> *brand = brands.findElement(Element<string>(listunit->data.brand));
	brand->deletePointer(listunit);

	Element<string> *model = models.findElement(Element<string>(listunit->data.model));
	model->deletePointer(listunit);

	Element<Type> *type = types.findElement(Element<Type>(listunit->data.type));
	type->deletePointer(listunit);

	Element<int> *size = sizes.findElement(Element<int>((listunit->data.size/10)*10));
	size->deletePointer(listunit);

	Element<int> *price = prices.findElement(Element<int>((listunit->data.price/10)*10));
	price->deletePointer(listunit);
}
