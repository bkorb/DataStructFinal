
#include <iostream>
#include <string>
#include "Inventory.hpp"

using namespace std;

Date::Date(int _day, int _month, int _year){
	day = _day;
	month = _month;
	year = _year;
	value = 0;
	if(((year%4==0 && year%100!=0) || year%400==0) && month>2){
		value+=1;
	}
	value+=365*year+((year-1)/4+1)-((year-1)/100+1)+((year-1)/400+1);
	switch(month){
		case 1:{
			monthName = "January";
			value+=0;
			break;
		}case 2:{
			monthName = "February";
			value+=31;
			break;
		}case 3:{
			monthName = "March";
			value+=59;
			break;
		}case 4:{
			monthName = "April";
			value+=90;
			break;
		}case 5:{
			monthName = "May";
			value+=120;
			break;
		}case 6:{
			monthName = "June";
			value+=151;
			break;
		}case 7:{
			monthName = "July";
			value+=181;
			break;
		}case 8:{
			monthName = "August";
			value+=212;
			break;
		}case 9:{
			monthName = "September";
			value+=243;
			break;
		}case 10:{
			monthName = "October";
			value+=273;
			break;
		}case 11:{
			monthName = "November";
			value+=304;
			break;
		}case 12:{
			monthName = "December";
			value+=334;
			break;
		}
	}
	value+=day;
}

Date::Date(int _value){
	value = _value;
	year = (400*value-303)/146097+1;
	int rem = value-(365*year+((year-1)/4+1)-((year-1)/100+1)+((year-1)/400+1));
	if(rem==60){
		day = 29;
		month = 2;
		monthName = "February";
		return;
	}
	if(((year%4==0 && year%100!=0) || year%400==0) && rem>=60){
		rem-=1;
	}
	if(rem<=31){
		month = 1;
		monthName = "January";
		rem-=0;
	}else if(rem<=59){
		month = 2;
		monthName = "February";
		rem-=31;
	}else if(rem<=90){
		month = 3;
		monthName = "March";
		rem-=59;
	}else if(rem<=120){
		month = 4;
		monthName = "April";
		rem-=90;
	}else if(rem<=151){
		month = 5;
		monthName = "May";
		rem-=120;
	}else if(rem<=181){
		month = 6;
		monthName = "June";
		rem-=151;
	}else if(rem<=212){
		month = 7;
		monthName = "July";
		rem-=181;
	}else if(rem<=243){
		month = 8;
		monthName = "August";
		rem-=212;
	}else if(rem<=273){
		month = 9;
		monthName = "September";
		rem-=243;
	}else if(rem<=304){
		month = 10;
		monthName = "October";
		rem-=273;
	}else if(rem<=334){
		month = 11;
		monthName = "November";
		rem-=304;
	}else if(rem<=365){
		month = 12;
		monthName = "December";
		rem-=334;
	}
	day = rem;
}

bool Date::operator>(const Date &other){
	return value>other.value;
}

bool Date::operator<(const Date &other){
	return value<other.value;
}

bool Date::operator==(const Date &other){
	return value==other.value;
}

bool Date::operator!=(const Date &other){
	return !(*this==other);
}

int Date::operator-(const Date &other){
	return value-other.value;
}

void Date::operator=(const Date &other){
	monthName = other.monthName;
	day = other.day;
	month = other.month;
	year = other.year;
	value = other.value;
}

Date::Date(){
	monthName = "null";
	day = -1;
	month = -1;
	year = -1;
	value = -1;
}

Date::Date(const Date &old){
	monthName = old.monthName;
	day = old.day;
	month = old.month;
	year = old.year;
	value = old.value;
}

bool AvailabilityNode::intersects(Date a, Date b){
	return !(b<start || a>end);
}

bool Availability::isAvailable(Date a, Date b){
	AvailabilityNode *node = head;
	while(node){
		if(node->intersects(a, b)){
			cout << "false" << endl;
			return false;
		}
		node = node->next;
	}
	cout << "true" << endl;
	return true;
}

void Availability::addHold(Date a, Date b){
	AvailabilityNode *node = new AvailabilityNode(a, b);
	node->next = head;
	head = node;
}

void Availability::removeHold(Date a, Date b){
	AvailabilityNode *node = head;
	if(head==nullptr){
		return;
	}
	if(head->start==a && head->end==b){
		head = head->next;
		return;
	}
	while(node->next){
		if(node->next->start==a && node->next->end==b){
			node->next = node->next->next;
		}
	}
}

string Availability::serialize(){
	string ret = "";
	AvailabilityNode *node = head;
	if(node){
		ret+=to_string(head->start.value)+":"+to_string(head->end.value);
		node = node->next;
	}
	while(node){
		ret+="!"+to_string(node->start.value)+":"+to_string(node->end.value);
		node = node->next;
	}
	return ret;
}

void Availability::readLine(string line){
	istringstream ss(line);
	string hold;
	while(getline(ss, hold, '!')){
		istringstream ss2(hold);
		string sstart;
		string send;
		getline(ss2, sstart, ':');
		getline(ss2, send, ':');
		addHold(Date(stoi(sstart)), Date(stoi(send)));
	}
}

//Ski class main constructor
Ski::Ski(string _brand, string _model, Type _type, int _size, int _price, int _cost, int _id){
	brand = _brand;
	model = _model;
	type = _type;
	size = _size;
	price = _price;
	cost = _cost;
	repairs = 0;
	costOfRepairs = 0;
	id = _id;
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
	avail = old.avail;
	id = old.id;
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
	id = -1;
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

	string sid;
	getline(ss, sid, ',');
	id = stoi(sid);

	string savail;
	getline(ss, savail, ',');
	avail.readLine(savail);
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
	return brand+","+model+","+to_string(type)+","+to_string(size)+","+to_string(price)+","+to_string(cost)+","+to_string(repairs)+","+to_string(costOfRepairs)+","+to_string(id)+","+avail.serialize();
}

//Function that allows ski objects to be printed
ostream & operator<<(ostream &Str, const Ski &v) {
	Str << v.type << ": " << v.brand << " " << v.model << ", " << v.size << "cm, $" << v.price;
	return Str;
}

bool Ski::operator==(const Ski &other){
	return (id==other.id);
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
	return (this->start == other.start && this->end == other.end && this->groupSize == other.groupSize && this->timestamp == other.timestamp);
}

bool Reservation::operator!=(const Reservation &other){
	return !(*this == other);
}

bool Reservation::operator>(const Reservation &other){
	if(this->start == other.start){
		if(this->groupSize == other.groupSize){
			return this->timestamp < other.timestamp;
		}else{
			return this->groupSize > other.groupSize;
		}
	}else{
		return this->start < other.start;
	}
}

bool Reservation::operator<(const Reservation &other){
	if(this->start == other.start){
		if(this->groupSize == other.groupSize){
			return this->timestamp > other.timestamp;
		}else{
			return this->groupSize < other.groupSize;
		}
	}else{
		return this->start > other.start;
	}
}

string Reservation::serialize(){
	string ret = "";
	ret += to_string(start.value);
	ret += ";"+to_string(end.value);
	ret += ";"+to_string(timestamp);
	ret += ";"+to_string(cost);
	ret += ";"+groupName;
	ret += ";"+to_string(groupSize);
	for(int i = 0; i<groupSize; i++){
		ret += ";"+to_string(skis[i]->data.id);
	}
	return ret;
}

Reservation::Reservation(ListTable<Ski> &units, string line){
	istringstream ss(line);

	string sstart;
	getline(ss, sstart, ';');
	start = Date(stoi(sstart));

	string send;
	getline(ss, send, ';');
	end = Date(stoi(send));

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
		string sid;
		getline(ss, sid, ';');
		Ski idski;
		idski.id = stoi(sid);
		skis[i] = (Element<Ski> *)units.findElement(idski);
	}
}

int Reservation::duration(){
	return end-start;
}

void Reservation::cancel(){
	for(int i = 0; i<groupSize; i++){
		skis[i]->data.avail.removeHold(start, end);
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
	ret += ";"+to_string(ski->data.id);
	return ret;
}

//Not done
ReturnItem::ReturnItem(ListTable<Ski> &units, string line){
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

	string sid;
	getline(ss, sid, ';');
	Ski idski;
	idski.id = stoi(sid);
	ski = (Element<Ski> *)units.findElement(idski);
}

//Function to add a new unit to the inventory
void Inventory::addUnit(string brand, string model, Type type, int size, int price, int cost){
	Ski ski(brand, model, type, size, price, cost, id);
	id++;
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
Element<Ski> **Inventory::searchUnits(string *brandList, int numBrands, string *modelList, int numModels, Type *typeList, int numTypes, int *sizeList, int numSizes, int *priceList, int numPrices, Date start, Date end, int &entries){
	if(numBrands==0 && numModels==0 && numTypes==0 && numSizes==0 && numPrices==0){
		int num = 0;
		string *search = brands.getQueries(num);
		int allelements = 0;
		AbstractElement **allunits = getQueryPointers<string>(brands, search, num, allelements);
		Element<Ski> **units = new Element<Ski>*[allelements];
		entries = 0;
		for(int i = 0; i<allelements; i++){
			Element<Ski> *unit = (Element<Ski> *)allunits[i];
			Date null;
			if(start==null || end==null || unit->data.avail.isAvailable(start, end)){
				units[entries] = unit;
				entries++;
			}
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
			Element<Ski> *unit = (Element<Ski> *)allunits[i];
			Date null;
			if(start==null || end==null || unit->data.avail.isAvailable(start, end)){
				if(size==elements){
					doublePointerArray(units, size, elements);
				}
				insertIntoPointerArray(units, size, elements, allunits[i]);
			}
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

string Inventory::saveToFile(){
    stringstream file;
	ListElement<Ski> *node = units.head;
	while(node){
		string line = node->data.serialize();
		file << line << endl;
		node = node->next;
	}
	file << "BREAK" << endl;
	file << orders.serialize();
	file << "BREAK" << endl;
	file << returns.serialize();
	file << "BREAK" << endl;
	file << groups.serialize();
	file << "BREAK" << endl;
	file << id;
    return file.str();
}

//Still needs queue implementation
void Inventory::loadFromFile(stringstream &file){
        string line;
	while(getline(file, line) && line!="BREAK"){
		Ski ski(line);
		addUnit(ski);
	}
	while(getline(file, line) && line!="BREAK"){
		Reservation res(units, line);
		orders.enqueue(res);
	}
	while(getline(file, line) && line!="BREAK"){
		ReturnItem res(units, line);
		returns.enqueue(res);
	}
	while(getline(file, line) && line!="BREAK"){
		istringstream ss(line);
		string key;
		string data;
		getline(ss, key, ':');
		getline(ss, data, ':');
		cout << key << ": " << data << endl;
		Reservation res(units, data);
		groups.insert(key, res);
	}
	string sid;
	getline(file, sid);
	id = stoi(sid);
}

void Inventory::addToOrders(Reservation order){
	for(int i = 0; i<order.groupSize; i++){
		order.skis[i]->data.avail.addHold(order.start, order.end);
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
	price = price * res.duration();
	return price;
}
