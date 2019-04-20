#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Database.hpp"
#include "priorityQueue.hpp"

using namespace std;

//Type enum definition
enum Type {null=0, ski=1, snowboard=2};

//Ski class definition
class Ski{
public:
	string brand;
	string model;
	Type type;
	int size;
	int price;
	int cost;
	int repairs;
	int costOfRepairs;
	Ski(string _brand, string _model, Type _type, int _size, int _price, int _cost);
	Ski();
	Ski(string line);
	Ski(const Ski &old);
	~Ski();
	string serialize();
	friend ostream & operator<<(ostream &Str, const Ski &v);
};

class Reservation: public GroupNode{
public:
	Element<Ski> **skis;
	int groupSize;
	int month;
	int day;
	int duration;
	int cost;
	int timestamp;
	string serialize();
	GroupNode(string line);
	Reservation(): skis(nullptr), groupSize(-1), month(-1), day(-1), duration(-1), cost(-1), timestamp(-1){}
	Reservation(Element<Ski> **_skis, int _groupSize, int _month, int _day, int _duration, int _cost, int _timestamp): skis(_skis), groupSize(_groupSize), month(_month), day(_day), duration(_duration), cost(_cost), timestamp(_timestamp){}
}

class ReturnItem: public GroupNode{
public:
	Element<Ski> *ski;
	bool repairNeeded;
	int costOfRepair;
	int timestamp;
	string serialize();
	ReturnItem(string line);
	ReturnItem(): repairNeeded(false), costOfRepair(-1), timestamp(-1){}
	ReturnItem(bool _repairNeeded, int _costOfRepair, int _timestamp): repairNeeded(_repairNeeded), costOfRepair(_costOfRepair), timestamp(_timestamp){}; 
}

//Inventory class definition
class Inventory{
public:
	ArrayTable<string> brands;
	ArrayTable<string> models;
	ArrayTable<Type> types;
	ArrayTable<int> sizes;
	ArrayTable<int> prices;
	ListTable<Ski> units;
	PriorityQueue orders;
	
	PriorityQueue returns;
	void addUnit(string brand, string model, Type type, int size, int price, int cost);
	void addUnit(Ski ski);
	void addUnit(ListElement<Ski> *ski);
	Element<Ski> **searchUnits(string *brandList, int numBrands, string *modelList, int numModels, Type *typeList, int numTypes, int *sizeList, int numSizes, int *priceList, int numPrices, int &entries);
	void removeUnit(Element<Ski> *unit);
	void saveToFile(string filename);
	void loadFromFile(string filename);
	void addToOrders(Reservation order);
	Reservation fillOrder();
	void addToReturns(Reservation item);
	Element<Ski> *returnItem();
};

//Type enum print function definition
ostream & operator<<(ostream &Str, const Type &v);

//Sorting function definitions
void sortByModel(Element<Ski> **&units, int low, int high);
void sortByBrand(Element<Ski> **&units, int low, int high);
void sortByType(Element<Ski> **&units, int low, int high);
void sortBySize(Element<Ski> **&units, int low, int high);
void sortByPrice(Element<Ski> **&units, int low, int high);