#include <iostream>
#include <string>
#include "Database.hpp"

using namespace std;

enum Type {null=0, ski=1, snowboard=2};

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
	Ski(const Ski &old);
	~Ski();
	friend ostream & operator<<(ostream &Str, const Ski &v);
};

class Inventory{
public:
	ArrayTable<string> brands;
	ArrayTable<string> models;
	ArrayTable<Type> types;
	ArrayTable<int> sizes;
	ArrayTable<int> prices;
	ListTable<Ski> units;
	void addUnit(string brand, string model, Type type, int size, int price, int cost);
	void addUnit(Ski ski);
	Element<Ski> **searchUnits(string *brandList, int numBrands, string *modelList, int numModels, Type *typeList, int numTypes, int *sizeList, int numSizes, int *priceList, int numPrices, int &entries);
	void removeUnit(Element<Ski> *unit);
};