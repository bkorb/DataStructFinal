#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include "Database.hpp"
#include "priorityQueue.hpp"
#include "Trie.hpp"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

using namespace std;

//Type enum definition
enum Type {null=0, ski=1, snowboard=2};

class Date{
public:
	string monthName;
	int day;
	int month;
	int year;
	int value;
	Date();
	Date(int _day, int _month, int _year);
	Date(int _value);
	Date(const Date &old);
	void operator=(const Date &other);
	bool operator>(const Date &other);
	bool operator<(const Date &other);
	bool operator==(const Date &other);
	bool operator!=(const Date &other);
	int operator-(const Date &other);
};

class AvailabilityNode{
public:
	Date start;
	Date end;
	AvailabilityNode *next;
	AvailabilityNode(Date _start, Date _end): start(_start), end(_end), next(nullptr){}
	bool intersects(Date a, Date b);
};

class Availability{
public:
	AvailabilityNode *head;
	bool isAvailable(Date a, Date b);
	void addHold(Date a, Date b);
	void removeHold(Date a, Date b);
	string serialize();
	Availability():head(nullptr){}
	void readLine(string line);
};

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
	int id;
	Availability avail; //Needs Serialization
	Ski(string _brand, string _model, Type _type, int _size, int _price, int _cost, int _id);
	Ski();
	Ski(string line);
	Ski(const Ski &old);
	~Ski();
	string serialize();
	friend ostream & operator<<(ostream &Str, const Ski &v);
	bool operator==(const Ski &other);
};

class Reservation{
public:
	Element<Ski> **skis;
	int groupSize;
	Date start;
	Date end;
	int cost;
	int timestamp;
	string groupName;
	bool operator>(const Reservation &other);
	bool operator<(const Reservation &other);
	bool operator==(const Reservation &other);
	bool operator!=(const Reservation &other);
	string serialize();
	int duration();
	Reservation(ListTable<Ski> &units, string line);
	Reservation(): skis(nullptr), groupSize(-1), start(0), end(0), cost(-1), timestamp(-1), groupName("null"){}
	Reservation(Element<Ski> **_skis, int _groupSize, Date _start, Date _end, int _cost, int _timestamp, string _groupName): skis(_skis), groupSize(_groupSize), start(_start), end(_end), cost(_cost), timestamp(_timestamp), groupName(_groupName){}
	void cancel();
};

class ReturnItem{
public:
	Element<Ski> *ski;
	bool repairNeeded;
	int costOfRepair;
	int timestamp;
	bool operator>(const ReturnItem &other);
	bool operator<(const ReturnItem &other);
	bool operator==(const ReturnItem &other);
	bool operator!=(const ReturnItem &other);
	string serialize();
	ReturnItem(ListTable<Ski> &units, string line);
	ReturnItem(const ReturnItem &old): ski(old.ski), repairNeeded(old.repairNeeded), costOfRepair(old.costOfRepair), timestamp(old.timestamp){}
	ReturnItem(): repairNeeded(false), costOfRepair(-1), timestamp(-1){}
	ReturnItem(bool _repairNeeded, int _costOfRepair, int _timestamp): repairNeeded(_repairNeeded), costOfRepair(_costOfRepair), timestamp(_timestamp){};
};

//Inventory class definition
class Inventory{
public:
	int id;
	ArrayTable<string> brands;
	ArrayTable<string> models;
	ArrayTable<Type> types;
	ArrayTable<int> sizes;
	ArrayTable<int> prices;
	ListTable<Ski> units;
	PriorityQueue<Reservation> orders;
	Trie<Reservation> groups;
	PriorityQueue<ReturnItem> returns;
	void addUnit(string brand, string model, Type type, int size, int price, int cost);
	void addUnit(Ski ski);
	void addUnit(ListElement<Ski> *ski);
	Element<Ski> **searchUnits(string *brandList, int numBrands, string *modelList, int numModels, Type *typeList, int numTypes, int *sizeList, int numSizes, int *priceList, int numPrices, Date start, Date end, int &entries);
	void removeUnit(Element<Ski> *unit);
    string saveToFile();
    void loadFromFile(stringstream &file);
	void addToOrders(Reservation order);
	void fillOrder();
	Reservation *findGroup(string groupName, int &entries);
	void removeFromGroups(Reservation group);
	void addToReturns(ReturnItem group);
	Element<Ski> *returnItem();
	Inventory():id(0){}
};

//Type enum print function definition
ostream & operator<<(ostream &Str, const Type &v);

//Sorting function definitions
void sortByModel(Element<Ski> **&units, int low, int high);
void sortByBrand(Element<Ski> **&units, int low, int high);
void sortByType(Element<Ski> **&units, int low, int high);
void sortBySize(Element<Ski> **&units, int low, int high);
void sortByPrice(Element<Ski> **&units, int low, int high);

int salesCost(Ski unit);
int rentalPrice(Reservation res);
