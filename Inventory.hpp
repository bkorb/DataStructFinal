#include <iostream>
#include <string>
#include "Database.hpp"

using namespace std;

enum Type {null=0, ski=1, snowboard=2};

class Ski{
private:
	string brand;
	string model;
	Type type;
	int size;
	int price;
	int cost;
	int repairs;
	int costOfRepairs;
public:
	Ski(string _brand, string _model, Type _type, int _size, int _price, int _cost);
	Ski();
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
	void addUnit(string brand, string model, Type type, int size, int price, int cost);
	Element<Ski> **searchUnits(string *brands, string *models, Type *types, int *sizes, int *prices);
	void removeUnit(Element<Ski> *unit);
};