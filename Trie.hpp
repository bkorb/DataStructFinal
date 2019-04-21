#include <string>
#include <vector>
#include <iostream>

using namespace std;

template <class T>
class LLNode{
public:
	LLNode<T> *next;
	T data;
	LLNode(T _data): data(_data){}
};

template <class T>
class TrieNode{
public:
	bool isLeaf;
	int size;
	char value;
	LLNode<T> *head;
	TrieNode<T> **children;
	TrieNode(int _size, char value);
};

template <class T>
class Trie{
public:
	TrieNode<T> **children;
	int size;
	void insert(string key, T data);
	T *search(string key, int &entries);
	void remove(string key, T data);
	Trie(int _size);
	Trie();
	~Trie();
};

template <class T>
TrieNode<T>::TrieNode(int _size, char _value){
	isLeaf = false;
	size = _size;
	value = _value;
	head = nullptr;
	children = new TrieNode<T>*[size];
	for(int i = 0; i<size; i++){
		children[i] = nullptr;
	}
}

template <class T>
Trie<T>::Trie(int _size){
	size = _size;
	children = new TrieNode<T>*[size];
	for(int i = 0; i<size; i++){
		children[i] = nullptr;
	}
}

template <class T>
Trie<T>::Trie(){
	size = 26;
	children = new TrieNode<T>*[size];
	for(int i = 0; i<size; i++){
		children[i] = nullptr;
	}
}

template <class T>
Trie<T>::~Trie(){
	//Nothing to do
}

template <class T>
void Trie<T>::insert(string key, T data){
	TrieNode<T> **array = children;
	for(int i = 0; i<key.length()-1; i++){
		int index = key[i] - 'a';
		if(array[index]){
			array = array[index]->children;
		}else{
			TrieNode<T> *node = new TrieNode<T>(size, key[i]);
			array[index] = node;
			array = array[index]->children;
		}
	}
	int index = key[key.length()-1]-'a';
	if(!array[index]){
		TrieNode<T> *node = new TrieNode<T>(size, key[index]);
		array[index] = node;
	}
	array[index]->isLeaf = true;
	LLNode<T> *node = new LLNode<T>(data);
	node->next = array[index]->head;
	array[index]->head = node;
}

template <class T>
void removeLLNode(T data, LLNode<T> *&head){
	LLNode<T> *curr = head;
	if(curr){
		if(curr->data == data){
			head = head->next;
			return;
		}
		LLNode<T> *prev = head;
		curr = curr->next;
		while(curr){
			if(curr->data == data){
				prev->next = curr->next;
				return;
			}
		}
	}
}

template <class T>
vector<T> getAllEntries(TrieNode<T> *node){
	vector<T> vec;
	LLNode<T> *head = node->head;
	while(head){
		vec.push_back(head->data);
		head = head->next;
	}
	for(int i = 0; i<node->size; i++){
		if(node->children[i]){
			vector<T> v = getAllEntries<T>(node->children[i]);
			vec.insert(vec.end(), v.begin(), v.end());
		}
	}
	return vec;
}

template <class T>
T *Trie<T>::search(string key, int &entries){
	TrieNode<T> *node;
	TrieNode<T> **array = children;
	for(int i = 0; i<key.length(); i++){
		int index = key[i]-'a';
		if(array[index]){
			node = array[index];
			array = array[index]->children;
		}else{
			entries = 0;
			return nullptr;
		}
	}
	vector<T> vec = getAllEntries<T>(node);
	entries = vec.size();
	T *ret = new T[entries];
	for(int i = 0; i<entries; i++){
		ret[i] = vec[i];
	}
	return ret;
}

template <class T>
void Trie<T>::remove(string key, T data){
	TrieNode<T> *node;
	TrieNode<T> **array = children;
	for(int i = 0; i<key.length(); i++){
		int index = key[i]-'a';
		if(array[index]){
			node = array[index];
			array = array[index]->children;
		}else{
			return;
		}
	}
	removeLLNode<T>(data, node->head);
}