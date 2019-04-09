#include <iostream>
#include <string>

using namespace std;

#define SIZE 2

struct AbstractElement{
public:
	string type;
};

template <class T>
class Element : public AbstractElement{
protected:
	AbstractElement **pointers;
	int size;
	int entries;
public:
	T data;
	Element();
	Element(const Element<T> &old);
	Element(T _data);
	~Element();
	void addPointer(AbstractElement *element);
	AbstractElement **getPointers(int &_entries);
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
	Element<T> *array;
	int size;
	int entries;
public:
	ArrayTable();
	~ArrayTable();
	Element<T> *addElement(Element<T> element);
	void printTable();
	Element<T> *findElement(Element<T> element);
};

template <class T>
class ListTable{
private:
	ListElement<T> *head;
public:
	ListTable();
	~ListTable();
	void addElement(ListElement<T> *element);
	void deleteElement(ListElement<T> *element);
};

template <class T>
Element<T>::Element(){
	data = T();
	type = typeid(T).name();
	pointers = new AbstractElement*[1];
	size = 1;
	entries = 0;
}

template <class T>
Element<T>::Element(T _data){
	type = typeid(T).name();
	data = _data;
	pointers = new AbstractElement*[1];
	size = 1;
	entries = 0;
}

template <class T>
Element<T>::Element(const Element<T> &old){
	type = typeid(T).name();
	data = old.data;
	pointers = new AbstractElement*[old.size];
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

void doublePointerArray(AbstractElement **&elements, int &size, int entries){
	AbstractElement **replacement = new AbstractElement*[size*2];
	for(int i = 0; i<entries; i++){
		replacement[i] = elements[i];
	}
	AbstractElement **temp = elements;
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

void insertIntoPointerArray(AbstractElement **&elements, int size, int entries, AbstractElement *element){
	if(entries==0){
		elements[0] = element;
		return;
	}

	if(element>elements[entries-1]){
		elements[entries] = element;
		return;
	}

	int start = 0;
	int end = entries-1;
	while(start<end){
		int index = (start+end)/2;
		if(element > elements[index]){
			start = index+1;
		}else{
			end = index;
		}
	}
	for(int i = entries; i>start; i--){
		elements[i] = elements[i-1];
	}
	elements[start] = element;
}

template <class T>
Element<T> *insertIntoArray(Element<T> *&array, int size, int entries, Element<T> element){
	if(entries==0){
		array[0] = element;
		return array;
	}

	if(element.data>array[entries-1].data){
		array[entries] = element;
		return array+entries;
	}

	int start = 0;
	int end = entries-1;
	while(start<end){
		int index = (start+end)/2;
		if(element.data > array[index].data){
			start = index+1;
		}else{
			end = index;
		}
	}
	for(int i = entries; i>start; i--){
		array[i] = array[i-1];
	}
	array[start] = element;
	return array+start;
}

template <class T>
void Element<T>::addPointer(AbstractElement *element){
	if(entries>=size){
		doublePointerArray(pointers, size, entries);
	}
	insertIntoPointerArray(pointers, size, entries, element);
	entries++;
}

template <class T>
AbstractElement **Element<T>::getPointers(int &_entries){
	_entries = entries;
	return pointers;
}

template <class T>
ListElement<T>::ListElement(){
	this->data = T();
	this->type = typeid(T).name();
	this->size = 1;
	this->entries = 0;
	next = nullptr;
	prev = nullptr;
}

template <class T>
ListElement<T>::ListElement(T _data){
	this->type = typeid(T).name();
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
ArrayTable<T>::ArrayTable(){
	array = new Element<T>[1];
	size = 1;
	entries = 0;
}

template <class T>
ArrayTable<T>::~ArrayTable(){
	delete[] array;
}

template <class T>
Element<T> *ArrayTable<T>::addElement(Element<T> element){
	if(entries==size){
		doubleArray<T>(array, size, entries);
	}
	Element<T> *pointer = insertIntoArray(array, size, entries, element);
	entries++;
	return pointer;
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
ListTable<T>::ListTable(){
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
		element->next = head;
		head->prev = element;
		head = element;
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