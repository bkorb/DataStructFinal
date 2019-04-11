#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Inventory.hpp"

using namespace std;

void readFileIntoInventory(string filename, Inventory &inventory){
	ifstream file(filename);
	string line;
	int i = 0;
	while(getline(file, line)){
		string brand;
		string model;
		Type type;
		string typestring;
		int size;
		string sizestring;
		int price;
		string pricestring;

		istringstream ss(line);
		getline(ss, brand, ',');
		getline(ss, model, ',');
		getline(ss, typestring, ',');
		if(typestring=="ski"){
			type = ski;
		}else{
			type = snowboard;
		}
		getline(ss, sizestring, ',');
		size = stoi(sizestring);
		getline(ss, pricestring, ',');
		price = stoi(pricestring);
		//cout << inventory << endl;
		inventory.addUnit(brand, model, type, size, price, 0);
		i++;
	}
	file.close();
}

int main(){
	Inventory inventory;
	readFileIntoInventory("skis.csv", inventory);
	cout << "Brands: " << endl;
	inventory.brands.printTable();
	cout << "Models: " << endl;
	inventory.models.printTable();
	cout << "Types: " << endl;
	inventory.types.printTable();
	cout << "Sizes: " << endl;
	inventory.sizes.printTable();
	cout << "Prices: " << endl; 
	inventory.prices.printTable();
	string brands[] = {"Faction"};
	string models[] = {};
	Type types[] = {};
	int sizes[] = {};
	int prices[] = {};

	int entries;
	Element<Ski> **units = inventory.searchUnits(brands, 1, models, 0, types, 0, sizes, 0, prices, 0, entries);
	cout << "Found: " << entries << endl;
	for(int i = 0; i<entries; i++){
		Ski unit = units[i]->data;
		cout << unit.brand << ", " << unit.model << ", " << unit.size << endl;
	}

	Element<Ski> *choice = units[0];
	cout << choice << endl;
	inventory.removeUnit(choice);

	units = inventory.searchUnits(brands, 1, models, 0, types, 0, sizes, 0, prices, 0, entries);
	cout << "Found: " << entries << endl;
	for(int i = 0; i<entries; i++){
		Ski unit = units[i]->data;
		cout << unit.brand << ", " << unit.model << ", " << unit.size << endl;
	}
	return 0;
}