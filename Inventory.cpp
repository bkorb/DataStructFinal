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

//Ski class copy constructor
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

//Destructor for Ski class
Ski::~Ski(){
	//Nothing to do
}

//Function that allows ski objects to be printed
ostream & operator<<(ostream &Str, const Ski &v) { 
	Str << v.type << ": " << v.brand << " " << v.model << ", " << v.size << "cm, $" << v.price;
	return Str;
}

ostream & operator<<(ostream &Str, const Type &v) { 
	if(v==ski){
		Str << "Ski";
	}else if(v==snowboard){
		Str << "Snowboard";
	}else{
		Str << "NULL";
	}
	return Str;
}

//Function to add a new unit to the inventory
void Inventory::addUnit(string brand, string model, Type type, int size, int price, int cost){
	Ski ski(brand, model, type, size, price, cost);
	addUnit(ski);
}

//Function to add a new unit to the inventory from Ski class
void Inventory::addUnit(Ski ski){
	//cout << "Adding " << ski << endl;
	ListElement<Ski> *unit = new ListElement<Ski>(ski);
	units.addElement(unit);

	Element<string> *foundBrand = brands.addElement(Element<string>(ski.brand));
	foundBrand->addPointer(unit);

	Element<string> *foundModel = models.addElement(Element<string>(ski.model));
	foundModel->addPointer(unit);

	Element<Type> *foundType = types.addElement(Element<Type>(ski.type));
	foundType->addPointer(unit);

	Element<int> *foundSize = sizes.addElement(Element<int>((ski.size/10)*10));
	foundSize->addPointer(unit);

	Element<int> *foundPrice = prices.addElement(Element<int>((ski.price/10)*10));
	foundPrice->addPointer(unit);
}

//Helper function to combine two sorted pointer arrays quickly
AbstractElement **combineSortedPointerArray(AbstractElement **a, int sizea, AbstractElement **b, int sizeb, int &elements){
	AbstractElement **c = new AbstractElement*[sizea+sizeb];
	int indexa = 0;
	int indexb = 0;
	int indexc = 0;
	elements = 0;
	while(indexa<sizea || indexb<sizeb){
		if(indexa==sizea){
			c[indexc] = b[indexb];
			indexb++;
		}else if(indexb==sizeb){
			c[indexc] = a[indexa];
			indexa++;
		}else{
			if(a[indexa]<b[indexb]){
				c[indexc] = a[indexa];
				indexa++;
			}else if(b[indexb]<a[indexa]){
				c[indexc] = b[indexb];
				indexb++;
			}else{
				c[indexc] = a[indexa];
				indexa++;
				indexb++;
			}
		}
		indexc++;
		elements++;
	}
	return c;
}

//Helper function to get all pointers for each given search parameter and
//combine them into a single array
template <class T>
AbstractElement **getQueryPointers(ArrayTable<T> &table, T *searchList, int numSearches, int &elements){
	AbstractElement **searchunits = new AbstractElement*[0];
	elements = 0;
	for(int i = 0; i<numSearches; i++){
		Element<T> search(searchList[i]);
		Element<T> *searchp = table.findElement(search);
		if(searchp!=nullptr){
			int entries = 0;
			AbstractElement **pointers = searchp->getPointers(entries);
			searchunits = combineSortedPointerArray(searchunits, elements, pointers, entries, elements);
		}
	}
	return searchunits;
}

//Funciton to query inventory for any combination of parameters and
//return all units that match
//TODO: speed up array combining
Element<Ski> **Inventory::searchUnits(string *brandList, int numBrands, string *modelList, int numModels, Type *typeList, int numTypes, int *sizeList, int numSizes, int *priceList, int numPrices, int &entries){
	if(numBrands==0 && numModels==0 && numTypes==0 && numSizes==0 && numPrices==0){
		int num = 0;
		string *search = brands.getQueries(num);
		int allelements = 0;
		AbstractElement **allunits = getQueryPointers<string>(brands, search, num, allelements);
		Element<Ski> **units = new Element<Ski>*[allelements];
		entries = allelements;
		for(int i = 0; i<allelements; i++){
			units[i] = (Element<Ski> *)allunits[i];
		}
		return units;
	}

	AbstractElement **allunits = new AbstractElement*[0];
	int allelements = 0;

	int brandelements = 0;
	AbstractElement **brandunits = getQueryPointers<string>(brands, brandList, numBrands, brandelements);
	allunits = combineSortedPointerArray(allunits, allelements, brandunits, brandelements, allelements);

	int modelelements = 0;
	AbstractElement **modelunits = getQueryPointers<string>(models, modelList, numModels, modelelements);
	allunits = combineSortedPointerArray(allunits, allelements, modelunits, modelelements, allelements);

	int typeelements = 0;
	AbstractElement **typeunits = getQueryPointers<Type>(types, typeList, numTypes, typeelements);
	allunits = combineSortedPointerArray(allunits, allelements, typeunits, typeelements, allelements);

	int sizeelements = 0;
	AbstractElement **sizeunits = getQueryPointers<int>(sizes, sizeList, numSizes, sizeelements);
	allunits = combineSortedPointerArray(allunits, allelements, sizeunits, sizeelements, allelements);

	int priceelements = 0;
	AbstractElement **priceunits = getQueryPointers<int>(prices, priceList, numPrices, priceelements);
	allunits = combineSortedPointerArray(allunits, allelements, priceunits, priceelements, allelements);

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

//Function to remove a unit from inventory
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

void swapElements(Element<Ski> *&a, Element<Ski> *&b){
	Element<Ski> *temp = a;
	a = b;
	b = temp;
}

void sortByBrand(Element<Ski> **&units, int low, int high){
	if(low<high){
		Element<Ski> *pivot = units[high];
		int i = low;
		for(int j = low; j<high; j++){
			if(units[j]->data.brand<=pivot->data.brand){
				swapElements(units[i], units[j]);
				i++;
			}
		}
		swapElements(units[i], units[high]);
		sortByBrand(units, low, i-1); 
	    sortByBrand(units, i+1, high);
	}
}

void sortByModel(Element<Ski> **&units, int low, int high){
	if(low<high){
		Element<Ski> *pivot = units[high];
		int i = low;
		for(int j = low; j<high; j++){
			if(units[j]->data.model<=pivot->data.model){
				swapElements(units[i], units[j]);
				i++;
			}
		}
		swapElements(units[i], units[high]);
		sortByModel(units, low, i-1); 
	    sortByModel(units, i+1, high);
	}
}

void sortByType(Element<Ski> **&units, int low, int high){
	if(low<high){
		Element<Ski> *pivot = units[high];
		int i = low;
		for(int j = low; j<high; j++){
			if(units[j]->data.type<=pivot->data.type){
				swapElements(units[i], units[j]);
				i++;
			}
		}
		swapElements(units[i], units[high]);
		sortByType(units, low, i-1); 
	    sortByType(units, i+1, high);
	}
}

void sortBySize(Element<Ski> **&units, int low, int high){
	if(low<high){
		Element<Ski> *pivot = units[high];
		int i = low;
		for(int j = low; j<high; j++){
			if(units[j]->data.size<=pivot->data.size){
				swapElements(units[i], units[j]);
				i++;
			}
		}
		swapElements(units[i], units[high]);
		sortBySize(units, low, i-1); 
	    sortBySize(units, i+1, high);
	}
}

void sortByPrice(Element<Ski> **&units, int low, int high){
	if(low<high){
		Element<Ski> *pivot = units[high];
		int i = low;
		for(int j = low; j<high; j++){
			if(units[j]->data.price<=pivot->data.price){
				swapElements(units[i], units[j]);
				i++;
			}
		}
		swapElements(units[i], units[high]);
		sortByPrice(units, low, i-1); 
	    sortByPrice(units, i+1, high);
	}
}
