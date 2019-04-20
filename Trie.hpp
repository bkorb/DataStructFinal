#include <string>

using namespace std;

template <class T>
class TrieNode{
public:
	bool isLeaf;
	int size;
	char value;
	T data;
	TrieNode *children;
	TrieNode(int _size, char value);
};

template <class T>
class Trie{
public:
	TrieNode *children;
	int size;
	void insert(string key, T data);
	Trie(int _size);
	~Trie();
};

