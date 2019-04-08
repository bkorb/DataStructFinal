#include <iostream>
#include <string>
#include "Database.hpp"

using namespace std;

template <class T>
Element<T>::Element(){
	size = 1;
	entries = 0;
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
	delete[] temp;
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
	delete[] temp;
}

template <class T>
void Element<T>::addPointer(Element<T> *element){
	if(entries==size){
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
void ArrayTable<T>::addElement(Element<T> *element){
	if(entries==size){
		doubleArray<T>(array, size, entries);
	}
	int i = 0;
	while(i<entries && element->data > array[i].data){
		i++;
	}
	for(int j = entries; j>i; j--){
		array[j] = array[j-1];
	}
	array[i] = *element;
}

template <class T>
Element<T> *searchArrayTable(Element<T> *array, Element<T> element, int start, int end){
	int index = (start+end)/2;
	if(array[index].data==element.data){
		return array+index;
	}else if(start==end){
		return nullptr;
	}else if(element.data>array[index].data){
		return searchArrayTable<T>(array, element, index, end);
	}else{
		return searchArrayTable<T>(array, element, start, index);
	}
}

template <class T>
Element<T> *ArrayTable<T>::findElement(Element<T> element){
	return searchArrayTable<T>(array, element, 0, entries-1);
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
		ListElement<T> *node = head;
		while(node->next && element->data > node->next->data){
			node = node->next;
		}
		element->prev = node;
		element->next = node->next;
		node->next->prev = element;
		node->next = element;
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