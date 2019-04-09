#include <iostream>
#include <string>

using namespace std;

//Abstract class that can hold any type of Element
struct AbstractElement{
public:
	string type;
};

//Template class that serves as a storage device for table elements
//that are stored in sorted arrays
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

//Template class that serves as a storage device for table elements
//that are stored in unsorted linked lists
template <class T>
class ListElement : public Element<T>{
public:
	ListElement *prev;
	ListElement *next;
	ListElement();
	ListElement(T _data);
	~ListElement();
};

//Template class that stores a sorted array of element classes
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

//Template class that stores an unsorted linked list of element classes
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

//Default constructor for Element class
template <class T>
Element<T>::Element(){
	data = T();
	type = typeid(T).name();
	pointers = new AbstractElement*[1];
	size = 1;
	entries = 0;
}

//Main constructor for Element class
template <class T>
Element<T>::Element(T _data){
	type = typeid(T).name();
	data = _data;
	pointers = new AbstractElement*[1];
	size = 1;
	entries = 0;
}

//Copy constructor for element class
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

//Destructor for Element class (TODO)
template <class T>
Element<T>::~Element(){
	for(int i = 0; i<entries; i++){
		delete pointers[i];
	}
	delete[] pointers;
}

//Helper function to double the size of an array of AbstractElement pointers (TODO)
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

//Helper function to double the size of an array of Elements
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

//Helper function to insert an AbstractElement pointer into an array of AbstractElement pointers
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

//Helper function to insert an Element into an array of Elements
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


//Function to add [a pointer to an Element in another table] to an Element
template <class T>
void Element<T>::addPointer(AbstractElement *element){
	if(entries>=size){
		doublePointerArray(pointers, size, entries);
	}
	insertIntoPointerArray(pointers, size, entries, element);
	entries++;
}

//Function to return all Elements in other tables pointed to by an Element
template <class T>
AbstractElement **Element<T>::getPointers(int &_entries){
	_entries = entries;
	return pointers;
}

//Default constructor for ListElement
template <class T>
ListElement<T>::ListElement(){
	this->data = T();
	this->type = typeid(T).name();
	this->size = 1;
	this->entries = 0;
	next = nullptr;
	prev = nullptr;
}

//Main constructor for ListElement
template <class T>
ListElement<T>::ListElement(T _data){
	this->type = typeid(T).name();
	this->size = 1;
	this->entries = 0;
	this->data = _data;
	next = nullptr;
	prev = nullptr;
}

//Destructor for ListElement (TODO)
template <class T>
ListElement<T>::~ListElement(){
	ListElement<T> *node = next;
	while(node){
		ListElement<T>* prev = node;
		node = node->next;
		delete prev;
	}
}

//Default constructor for ArrayTable
template <class T>
ArrayTable<T>::ArrayTable(){
	array = new Element<T>[1];
	size = 1;
	entries = 0;
}

//Destructor for ArrayTable (TODO)
template <class T>
ArrayTable<T>::~ArrayTable(){
	delete[] array;
}

//Function to add an Element to an ArrayTable in the correct place
template <class T>
Element<T> *ArrayTable<T>::addElement(Element<T> element){
	if(entries==size){
		doubleArray<T>(array, size, entries);
	}
	Element<T> *pointer = insertIntoArray(array, size, entries, element);
	entries++;
	return pointer;
}

//Function to print all Elements in an ArrayTable
template <class T>
void ArrayTable<T>::printTable(){
	for(int i = 0; i<entries; i++){
		cout << array[i].data << endl;
	}
}

//Helper function to find a matching Element in an array of Elements
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

//Function to find a matching Element in an ArrayTable
template <class T>
Element<T> *ArrayTable<T>::findElement(Element<T> element){
	int index = searchArrayTable<T>(array, element, 0, entries-1);
	if(index==-1){
		return nullptr;
	}else{
		return array+index;
	}
}

//Default constructor for ListTable
template <class T>
ListTable<T>::ListTable(){
	head = nullptr;
}

//Destructor for ListTable (TODO)
template <class T>
ListTable<T>::~ListTable(){
	ListElement<T> *node = head;
	while(node){
		ListElement<T>* prev = node;
		node = node->next;
		delete prev;
	}
}

//Function to add an Element to a ListTable
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

//Fucntion to remove an Element from a ListTable
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