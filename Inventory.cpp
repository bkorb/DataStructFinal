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
	size = -1;
	price = -1;
	cost = -1;
	repairs = -1;
	costOfRepairs = -1;
}

Ski::Ski(string line){
	istringstream ss(line);

	getline(ss, brand, ',');

	getline(ss, model, ',');

	string stype;
	getline(ss, stype, ',');
	if(stype=="ski"){
		type = ski;
	}else{
		type = snowboard;
	}

	string ssize;
	getline(ss, ssize, ',');
	size = stoi(ssize);

	string sprice;
	getline(ss, sprice, ',');
	price = stoi(sprice);

	string scost;
	getline(ss, scost, ',');
	cost = stoi(scost);

	string srepairs;
	getline(ss, srepairs, ',');
	repairs = stoi(srepairs);

	string scostrepairs;
	getline(ss, scostrepairs, ',');
	costOfRepairs = stoi(scostrepairs);
}

//Destructor for Ski class
Ski::~Ski(){
	//Nothing to do
}

string to_string(Type type){
	if(type==ski){
		return "ski";
	}else if(type==snowboard){
		return "snowboard";
	}else{
		return "null";
	}
}

string Ski::serialize(){
	return brand+","+model+","+to_string(type)+","+to_string(size)+","+to_string(price)+","+to_string(cost)+","+to_string(repairs)+","+to_string(costOfRepairs);
}

//Function that allows ski objects to be printed
ostream & operator<<(ostream &Str, const Ski &v) { 
	Str << v.type << ": " << v.brand << " " << v.model << ", " << v.size << "cm, $" << v.price;
	return Str;
}

//Function that allows type enum to be printed
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

bool Reservation::operator==(const Reservation &other){
	return (this->month == other.month && this->day == other.day && this->groupSize == other.groupSize && this->timestamp == other.timestamp);
}

bool Reservation::operator!=(const Reservation &other){
	return !(*this == other);
}

bool Reservation::operator>(const Reservation &other){
	if(this->month == other.month){
		if(this->day == other.day){
			if(this->groupSize == other.groupSize){
				return this->timestamp < other.timestamp;
			}else{
				return this->groupSize > other.groupSize;
			}
		}else{
			return this->day < other.day;
		}
	}else{
		return this->month < other.month;
	}
}

bool Reservation::operator<(const Reservation &other){
	if(this->month == other.month){
		if(this->day == other.day){
			if(this->groupSize == other.groupSize){
				return this->timestamp > other.timestamp;
			}else{
				return this->groupSize < other.groupSize;
			}
		}else{
			return this->day > other.day;
		}
	}else{
		return this->month > other.month;
	}
}

string Reservation::serialize(){
	string ret = "";
	ret += to_string(month);
	ret += ";"+to_string(day);
	ret += ";"+to_string(duration);
	ret += ";"+to_string(timestamp);
	ret += ";"+to_string(cost);
	ret += ";"+groupName;
	ret += ";"+to_string(groupSize);
	for(int i = 0; i<groupSize; i++){
		ret += ";"+skis[i]->data.serialize();
	}
	return ret;
}

Reservation::Reservation(string line){
	istringstream ss(line);

	string smonth;
	getline(ss, smonth, ';');
	month = stoi(smonth);

	string sday;
	getline(ss, sday, ';');
	day = stoi(sday);

	string sduration;
	getline(ss, sduration, ';');
	duration = stoi(sduration);

	string stimestamp;
	getline(ss, stimestamp, ';');
	timestamp = stoi(stimestamp);

	string scost;
	getline(ss, scost, ';');
	cost = stoi(scost);

	getline(ss, groupName, ';');

	string sgroupSize;
	getline(ss, sgroupSize, ';');
	groupSize = stoi(sgroupSize);

	skis = new Element<Ski>*[groupSize];

	for(int i = 0; i<groupSize; i++){
		string line;
		getline(ss, line, ';');
		skis[i] = new Element<Ski>(Ski(line));
	}
}

bool ReturnItem::operator==(const ReturnItem &other){
	return (this->repairNeeded == other.repairNeeded && this->costOfRepair == other.costOfRepair && this->timestamp == other.timestamp);
}

bool ReturnItem::operator!=(const ReturnItem &other){
	return !(*this == other);
}

bool ReturnItem::operator>(const ReturnItem &other){
	if(this->repairNeeded == other.repairNeeded){
		if(this->costOfRepair == other.costOfRepair){
			return this->timestamp < other.timestamp;
		}else{
			return this->costOfRepair < other.costOfRepair;
		}
	}else{
		return !(this->repairNeeded);
	}
}

bool ReturnItem::operator<(const ReturnItem &other){
	if(this->repairNeeded == other.repairNeeded){
		if(this->costOfRepair == other.costOfRepair){
			return this->timestamp > other.timestamp;
		}else{
			return this->costOfRepair > other.costOfRepair;
		}
	}else{
		return (this->repairNeeded);
	}
}

string ReturnItem::serialize(){
	string ret = "";
	ret += (repairNeeded)? "1" : "0";
	ret += ";"+to_string(costOfRepair);
	ret += ";"+to_string(timestamp);
	ret += ";"+ski->data.serialize();
	return ret;
}

//Not done
ReturnItem::ReturnItem(string line){
	istringstream ss(line);

	string srepairNeeded;
	getline(ss, srepairNeeded, ';');
	repairNeeded = (srepairNeeded=="1");

	string scostOfRepair;
	getline(ss, scostOfRepair, ';');
	costOfRepair = stoi(scostOfRepair);

	string stimestamp;
	getline(ss, stimestamp, ';');
	timestamp = stoi(stimestamp);

	string sski;
	getline(ss, sski, ';');
	ski = new Element<Ski>(Ski(sski));
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
	addUnit(unit);
}

void Inventory::addUnit(ListElement<Ski> *unit){
	units.addElement(unit);

	Element<string> *foundBrand = brands.addElement(Element<string>(unit->data.brand));
	foundBrand->addPointer(unit);

	Element<string> *foundModel = models.addElement(Element<string>(unit->data.model));
	foundModel->addPointer(unit);

	Element<Type> *foundType = types.addElement(Element<Type>(unit->data.type));
	foundType->addPointer(unit);

	Element<int> *foundSize = sizes.addElement(Element<int>((unit->data.size/10)*10));
	foundSize->addPointer(unit);

	Element<int> *foundPrice = prices.addElement(Element<int>((unit->data.price/10)*10));
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

void Inventory::saveToFile(string filename){
	ofstream file(filename);
	ListElement<Ski> *node = units.head;
	while(node){
		Ski ski = node->data;
		string line = ski.serialize();
		file << line << endl;
		node = node->next;
	}
	file << "BREAK" << endl;
	while(!orders.isEmpty()){
		Reservation res = orders.peek();
		file << res.serialize() << endl;
		orders.dequeue();
	}
	file << "BREAK" << endl;
	while(!orders.isEmpty()){
		ReturnItem res = returns.peek();
		file << res.serialize() << endl;
		returns.dequeue();
	}
	file.close();
}

//Still needs queue implementation
void Inventory::loadFromFile(string filename){
	ifstream file(filename);
	string line;
	while(getline(file, line) && line!="BREAK"){
		Ski ski(line);
		addUnit(ski);
	}
	while(getline(file, line) && line!="BREAK"){
		Reservation res(line);
		orders.enqueue(res);
	}
	while(getline(file, line)){
		ReturnItem res(line);
		returns.enqueue(res);
	}
	file.close();
}

void Inventory::addToOrders(Reservation order){
	for(int i = 0; i<order.groupSize; i++){
		removeUnit(order.skis[i]);
	}
	orders.enqueue(order);
}

void Inventory::fillOrder(){
	Reservation reservation = (Reservation)orders.peek();
	orders.dequeue();
	groups.insert(reservation.groupName, reservation);
}

Reservation *Inventory::findGroup(string groupName, int &entries){
	return groups.search(groupName, entries);
}

void Inventory::removeFromGroups(Reservation group){
	groups.remove(group.groupName, group);
}

void Inventory::addToReturns(ReturnItem item){
	returns.enqueue(item);
}

Element<Ski> *Inventory::returnItem(){
	ReturnItem item = (ReturnItem)returns.peek();
	returns.dequeue();
	addUnit((ListElement<Ski> *)item.ski);
	return item.ski;
}

//Helper function to swap two elements of an array
void swapElements(Element<Ski> *&a, Element<Ski> *&b){
	Element<Ski> *temp = a;
	a = b;
	b = temp;
}

//Function to sort array by brand
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

//Function to sort array by model
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

//Function to sort array by type
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

//Function to sort array by size
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

//Function to sort array by price
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

int salesCost(Ski unit)
{
	double sale;
	if(unit.costOfRepairs != 0)
	{
		if(unit.costOfRepairs > 20)
		{
			sale = (unit.cost * 0.60)/((1/20)* unit.costOfRepairs);
			return sale;
		}
		else if(unit.costOfRepairs > 10)
		{
			sale = (unit.cost * 0.60)/((1/10)* unit.costOfRepairs);
			return sale;
		}
		else
		{
			sale = (unit.cost * 0.60)/((1/5)* unit.costOfRepairs);
			return sale;
		}
	}
	else sale = (unit.cost * 0.60);
	return (int)sale;
}

int rentalPrice(Reservation res)
{
	int price = 0;
	for(int i = 0; i < res.groupSize; i++)
	{
		price = price + res.skis[i]->data.price;
	}
	price = price * res.duration;
	return price;
}