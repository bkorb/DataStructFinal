#include <iostream>
#include <string>

using namespace std;

#define SIZE 2

template <class T>
class Element{
protected:
	Element **pointers;
	int size;
	int entries;
public:
	T data;
	Element();
	Element(const Element<T> &old);
	Element(T _data);
	~Element();
	void addPointer(Element<T> *element);
	Element<T> **getPointers(int &_entries);
};

template <class T>
class ListElement : public Element<T>{
public:
	ListElement *prev;
	ListElement *next;
	ListElement();
	ListElement(T _data);
	~ListElement();
};

template <class T>
class ArrayTable{
private:
	string name;
	Element<T> *array;
	int size;
	int entries;
public:
	ArrayTable(string _name);
	~ArrayTable();
	void addElement(Element<T> element);
	void printTable();
	Element<T> *findElement(Element<T> element);
};

template <class T>
class ListTable{
private:
	string name;
	ListElement<T> *head;
public:
	ListTable(string _name);
	~ListTable();
	void addElement(ListElement<T> *element);
	void deleteElement(ListElement<T> *element);
};

template <class T>
Element<T>::Element(){
	pointers = new Element<T>*[1];
	size = 1;
	entries = 0;
}

template <class T>
Element<T>::Element(T _data){
	data = _data;
	pointers = new Element<T>*[1];
	size = 1;
	entries = 0;
}

template <class T>
Element<T>::Element(const Element<T> &old){
	data = old.data;
	pointers = new Element<T>*[old.size];
	for(int i = 0; i<old.entries; i++){
		pointers[i] = old.pointers[i];
	}
	size = old.size;
	entries = old.entries;
}

template <class T>
Element<T>::~Element(){
	for(int i = 0; i<entries; i++){
		delete pointers[i];
	}
	delete[] pointers;
}

template <class T>
void doublePointerArray(Element<T> **&elements, int &size, int entries){
	Element<T> **replacement = new Element<T>*[size*2];
	for(int i = 0; i<entries; i++){
		replacement[i] = elements[i];
	}
	Element<T> **temp = elements;
	elements = replacement;
	size*=2;
	//TODO: delete[] temp;
}

template <class T>
void doubleArray(Element<T> *&elements, int &size, int entries){
	Element<T> *replacement = new Element<T>[size*2];
	for(int i = 0; i<entries; i++){
		replacement[i] = elements[i];
	}
	Element<T> *temp = elements;
	elements = replacement;
	size*=2;
	//TODO: delete[] temp;
}

template <class T>
void Element<T>::addPointer(Element<T> *element){
	if(entries>=size){
		doublePointerArray<T>(pointers, size, entries);
	}
	pointers[entries] = element;
	entries++;
}

template <class T>
Element<T> **Element<T>::getPointers(int &_entries){
	_entries = entries;
	return pointers;
}

template <class T>
ListElement<T>::ListElement(){
	this->size = 1;
	this->entries = 0;
	next = nullptr;
	prev = nullptr;
}

template <class T>
ListElement<T>::ListElement(T _data){
	this->size = 1;
	this->entries = 0;
	this->data = _data;
	next = nullptr;
	prev = nullptr;
}

template <class T>
ListElement<T>::~ListElement(){
	ListElement<T> *node = next;
	while(node){
		ListElement<T>* prev = node;
		node = node->next;
		delete prev;
	}
}

template <class T>
ArrayTable<T>::ArrayTable(string _name){
	name = _name;
	array = new Element<T>[1];
	size = 1;
	entries = 0;
}

template <class T>
ArrayTable<T>::~ArrayTable(){
	delete[] array;
}

template <class T>
void ArrayTable<T>::addElement(Element<T> element){
	if(entries==size){
		doubleArray<T>(array, size, entries);
	}
	int i = 0;
	while(i<entries && element.data > array[i].data){
		i++;
	}
	for(int j = entries; j>i; j--){
		array[j] = array[j-1];
	}
	array[i] = element;
	entries++;
}

template <class T>
void ArrayTable<T>::printTable(){
	for(int i = 0; i<entries; i++){
		cout << array[i].data << endl;
	}
}

template <class T>
int searchArrayTable(Element<T> *array, Element<T> element, int start, int end){
	int index = (start+end)/2;
	if(array[index].data==element.data){
		return index;
	}else if(start>=end){
		return -1;
	}else if(element.data>array[index].data){
		return searchArrayTable<T>(array, element, index+1, end);
	}else{
		return searchArrayTable<T>(array, element, start, index-1);
	}
}

template <class T>
Element<T> *ArrayTable<T>::findElement(Element<T> element){
	int index = searchArrayTable<T>(array, element, 0, entries-1);
	if(index==-1){
		return nullptr;
	}else{
		return array+index;
	}
}

template <class T>
ListTable<T>::ListTable(string _name){
	name = _name;
	head = nullptr;
}

template <class T>
ListTable<T>::~ListTable(){
	ListElement<T> *node = head;
	while(node){
		ListElement<T>* prev = node;
		node = node->next;
		delete prev;
	}
}

template <class T>
void ListTable<T>::addElement(ListElement<T> *element){
	if(head){
		if(element->data < head->data){
			head->prev = element;
			head = element;
			return;
		}
		ListElement<T> *node = head;
		ListElement<T> *prev = nullptr;
		while(node && element->data > node->data){
			prev = node;
			node = node->next;
		}
		if(node){
			prev->next = element;
			element->prev = prev;
			node->prev = element;
			element->next = node;
		}else{
			prev->next = element;
			element->prev = prev;
			element->next = nullptr;
		}
	}else{
		head = element;
	}
}

template <class T>
void ListTable<T>::deleteElement(ListElement<T> *element){
	if(head==element){
		head = element->next;
		if(head){
			head->prev = nullptr;
		}
	}else{
		if(element->next){
			element->next->prev = element->prev;
		}
		element->prev->next = element->next;
	}
}