#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include "Inventory.hpp"

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
Element<Ski> **makeQuery(Inventory &inventory, int &num, Date start, Date end){
	int numBrands, numModels, numTypes, numSizes, numPrices;
	string *brands = getParameterArray<string>("Brand", inventory.brands, numBrands);
	string *models = getParameterArray<string>("Model", inventory.models, numModels);
	Type *types = getParameterArray("Type", inventory.types, numTypes);
	int *sizes = getParameterArray("Size", inventory.sizes, numSizes);
	int *prices = getParameterArray("Price", inventory.prices, numPrices);

	int entries;
	Element<Ski> **units = inventory.searchUnits(brands, numBrands, models, numModels, types, numTypes, sizes, numSizes, prices, numPrices, start, end, entries);
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
		cout << units[i]->data << endl;
		cout << i+1 << ". " << units[i]->data.serialize() << endl;
	}
	cout << "Choose (a) ski(s)" << endl;

	string choices;
	getline(cin, choices);

	num = 0;
	istringstream ss(choices);
	while(getline(ss, choice, ',')){
		num++;
	}
	Element<Ski> **parameters = new Element<Ski>*[num];
	istringstream ss1(choices);
	int index = 0;
	while(getline(ss1, choice, ',')){
		parameters[index] = units[stoi(choice)-1];
		index++;
	}
	return parameters;

	//decision = stoi(choice);
	//Element<Ski> *unit = units[decision-1];
	//cout << unit << endl;
	//Element<Ski> **arr = new Element<Ski>*[1];
	//arr[0] = unit;
}

void showMenu(){
	cout << "1. Search for items" << endl;
	cout << "2. Checkout" << endl;
	cout << "3. Sell items" << endl;
	cout << "4. Pick up gear" << endl;
	cout << "5. Make a return" << endl;
	cout << "6. Return an item to inventory" << endl;
	cout << "7. Add a ski/snowboard" << endl;
	cout << "8. Load inventory from save" << endl;
	cout << "9. Save inventory to file" << endl;
	cout << "10. Quit" << endl;
}

//Main
int main(int argc, char **argv){
	Inventory inventory;
	Element<Ski> **cart;
	int cartsize = 0;
	Date cstart;
	Date cend;
	while(true){
		showMenu();
		string choice;
		getline(cin, choice);
		int c = stoi(choice);
		switch(c){
			case 1:{
				cout << "Choose a start date:" << endl;
				string sday, smonth, syear;
				cout << "Enter day:" << endl;
				getline(cin, sday);
				cout << "Enter month:" << endl;
				getline(cin, smonth);
				cout << "Enter year:" << endl;
				getline(cin, syear);
				Date start(stoi(sday), stoi(smonth), stoi(syear));

				cout << "Choose an end date:" << endl;
				cout << "Enter day:" << endl;
				getline(cin, sday);
				cout << "Enter month:" << endl;
				getline(cin, smonth);
				cout << "Enter year:" << endl;
				getline(cin, syear);
				Date end(stoi(sday), stoi(smonth), stoi(syear));

				Element<Ski> **tskis = new Element<Ski>*[100];
				int items = 0;
				while(true){
					int num;
					Element<Ski> **skis = makeQuery(inventory, num, start, end);
					for(int i = 0; i<num; i++){
						tskis[items] = skis[i];
						items++;
					}
					cout << "Would you like to make another query? (y/n)" << endl;
					string repeat;
					getline(cin, repeat);
					if(repeat!="y"){
						cartsize = items;
						cart = tskis;
						cstart = start;
						cend = end;
						cout << "Items selected:" << endl;
						for(int i = 0; i<cartsize; i++){
							cout << cart[i]->data << endl;
						}
						break;
					}
				}
				break;
			}case 2:{
				cout << "Enter your group name: "<< endl;
				string gn;
				getline(cin, gn);
				Reservation res(cart, cartsize, cstart, cend, -1, (int)time(nullptr), gn);
				res.cost = rentalPrice(res);
				inventory.addToOrders(res);
				cout << "Checked out successfully" << endl;
				break;
			}case 3:{
				for(int i = 0; i<cartsize; i++){
					cout << "Sold " << cart[i]->data << " for $" << salesCost(cart[i]->data) << endl;
					inventory.removeUnit(cart[i]);
				}
				break;
			}case 4:{
				Reservation res = inventory.orders.peek();
				inventory.fillOrder();
				cout << "Group: " << res.groupName << " picked up gear" << endl;
				break;
			}case 5:{
				while(true){
					cout << "Enter group name:" << endl;
					string group;
					getline(cin, group);
					int elems;
					Reservation *gs = inventory.groups.search(group, elems);
					for(int i = 0; i<elems; i++){
						Reservation res = gs[i];
						cout << "Group " << (i+1) << " (" << res.groupName <<"):" << endl;
						for(int j = 0; j<res.groupSize; j++){
							cout << res.skis[j]->data << endl;
						}
						cout << endl;
					}
					cout << "Select group or type cancel to cancel search:" << endl;
					string choice;
					getline(cin, choice);
					if(choice=="cancel"){
						cout << "Search cancelled" << endl;
						break;
					}else if(choice!=""){
						int decision = stoi(choice)-1;
						Reservation res = gs[decision];
						inventory.removeFromGroups(res);
						for(int i = 0; i<res.groupSize; i++){
							Element<Ski> *ski = res.skis[i];
							cout << "Ski " << i << ": " << ski->data << endl;
							cout << "Repairs needed? (t/f)" << endl;
							string rns;
							getline(cin, rns);
							bool rn = (rns=="t");
							int cor = 0;
							if(rn){
								cout << "Enter cost of repairs:" << endl;
								string scor;
								getline(cin, scor);
								cor = stoi(scor);
							}
							int ts = (int)time(nullptr);
							ReturnItem ret(rn, cor, ts);
							ret.ski = ski;
							inventory.addToReturns(ret);
						}
						cout << "Group: " << res.groupName << " returned items" << endl;
						break;
					}
				}
				break;
			}case 6:{
				ReturnItem ret = inventory.returns.peek();
				inventory.returns.dequeue();
				cout << "Returned " << ret.ski->data << " with $" << ret.costOfRepair << " worth of repairs to inventory" << endl; 
				break;
			}case 7:{
				string brand;
				string model;
				Type type;
				int size;
				int price;
				int cost;
				cout << "Enter type:" << endl;
				string stype;
				getline(cin, stype);
				if(stype=="ski"){
					type = ski;
				}else{
					type = snowboard;
				}
				cout << "Enter brand:" << endl;
				getline(cin, brand);
				cout << "Enter model:" << endl;
				getline(cin, model);
				string ssize;
				cout << "Enter size:" << endl;
				getline(cin, ssize);
				size = stoi(ssize);
				string sprice;
				cout << "Enter price:" << endl;
				getline(cin, sprice);
				price = stoi(sprice);
				string scost;
				cout << "Enter cost:" << endl;
				getline(cin, scost);
				cost = stoi(scost);
				inventory.addUnit(brand, model, type, size, price, cost);
				cout << "New ski added" << endl;
				break;
			}case 8:{
				cout << "Enter file to load from:" << endl;
				string filename;
				getline(cin, filename);
				inventory.loadFromFile(filename);
				cout << "Inventory loaded from " << filename << endl;
				break;
			}case 9:{
				cout << "Enter file to save to:" << endl;
				string filename;
				getline(cin, filename);
				inventory.saveToFile(filename);
				cout << "Inventory saved to " << filename << endl;
				break;
			}case 10:{
				return 0;
				break;
			}
		}
	}
	//readFileIntoInventory("skis.csv", inventory);
	//inventory.saveToFile("save1.csv");

    /*QApplication app (argc, argv);

    QPushButton button ("Hello world !");
    button.show();

    return app.exec();*/

	/*cout << "start" << endl;
	Trie<string> test(26);
	test.insert("cat", "feline");
	test.insert("cat", "kitty");
	test.insert("cougar", "feline2");
	test.insert("dog", "canine");
	test.insert("human", "homosapien");
	test.insert("tree", "arbol");
	cout << "inserted" << endl;
	int entries;
	string *ret = test.search("c", entries);
	for(int i = 0; i<entries; i++){
		cout << ret[i] << endl;
	}
	test.remove("cat", "kitty");
	cout << endl;
	ret = test.search("c", entries);
	for(int i = 0; i<entries; i++){
		cout << ret[i] << endl;
	}
	test.remove("cougar", "feline2");
	cout << endl;
	ret = test.search("c", entries);
	for(int i = 0; i<entries; i++){
		cout << ret[i] << endl;
	}
	test.remove("cat", "feline");
	cout << endl;
	ret = test.search("c", entries);
	for(int i = 0; i<entries; i++){
		cout << ret[i] << endl;
	}*/

	return 0;
}
