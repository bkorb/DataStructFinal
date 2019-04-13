#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Inventory.hpp"
//#include <QApplication>
//#include <QPushButton>

using namespace std;

//Function to read ski data (format: Brand,Model,Type,Size,Price) into inventory
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
		inventory.addUnit(brand, model, type, size, price, 0);
		i++;
	}
	file.close();
}

//Function to get user input for a specific parameter
template <class T>
T *getParameterArray(string parameter, ArrayTable<T> &set, int &entries){
	entries = 0;
	int numOptions = 0;
	T *options = set.getQueries(numOptions);
	cout << parameter << " options: " << endl;
	for(int i = 0; i<numOptions; i++){
		cout << i+1 << ". " << options[i] << endl;
	}
	string choices;
	cout << "Enter your choices separated by commas or type all to select all options" << endl;
	getline(cin, choices);
	if(choices=="all" || choices=="a" || choices=="All" || choices=="A"){
		entries = 0;
		return nullptr;
	}
	istringstream ss(choices);
	string choice;
	while(getline(ss, choice, ',')){
		entries++;
	}
	T *parameters = new T[entries];
	istringstream ss1(choices);
	int index = 0;
	while(getline(ss1, choice, ',')){
		parameters[index] = options[stoi(choice)-1];
		index++;
	}
	return parameters;
}

//Function to prompt the user to make a query
void makeQuery(Inventory &inventory){
	int numBrands, numModels, numTypes, numSizes, numPrices;
	string *brands = getParameterArray<string>("Brand", inventory.brands, numBrands);
	string *models = getParameterArray<string>("Model", inventory.models, numModels);
	Type *types = getParameterArray("Type", inventory.types, numTypes);
	int *sizes = getParameterArray("Size", inventory.sizes, numSizes);
	int *prices = getParameterArray("Price", inventory.prices, numPrices);

	int entries;
	Element<Ski> **units = inventory.searchUnits(brands, numBrands, models, numModels, types, numTypes, sizes, numSizes, prices, numPrices, entries);
	cout << "Choose how to sort (defult price): " << endl;
	cout << "1. Sort by brand\n2. Sort by model\n3. Sort by type\n4. Sort by size\n5. Sort by price" << endl;
	string choice;
	getline(cin, choice);
	int decision = 5;
	if(choice==""){
		decision = 5;
	}else{
		decision = stoi(choice);
	}
	switch(decision){
		case 1: {
			sortByBrand(units, 0, entries-1);
			break;
		}
		case 2: {
			sortByModel(units, 0, entries-1);
			break;
		}
		case 3: {
			sortByType(units, 0, entries-1);
			break;
		}
		case 4: {
			sortBySize(units, 0, entries-1);
			break;
		}
		default: {
			sortByPrice(units, 0, entries-1);
			break;
		}
	}
	cout << "Found: " << entries << endl;
	for(int i = 0; i<entries; i++){
		cout << i+1 << ". " << units[i]->data << endl;
	}
}

//Main
int main(int argc, char **argv){
	Inventory inventory;
	readFileIntoInventory("skis.csv", inventory);

    /*QApplication app (argc, argv);

    QPushButton button ("Hello world !");
    button.show();

    return app.exec();*/

    while(true){
		makeQuery(inventory);
	}
	return 0;
}
