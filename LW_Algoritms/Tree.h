#pragma once
#include <iostream>
#include "listErrors.h"

using namespace std;

template <class Key = int, class Data = int>
class Tree {
private:

	class Node {
	public:
		Key key;
		Data data;
		int countSubNode;
		Node *left, *right;

		Node(Key key = Key(), Data data = Data(), int countSubNode = 1, Node* left = nullptr, Node* right = nullptr) : key(key), data(data), countSubNode(countSubNode), left(left), right(right) {}
	};

	int size;
	Node* root;

	void copy(Node* node);
	void clear(Node* node);
	bool insert(Key key, Data data, Node* parent, Node* cur);
	Node* getNode(Key key, Node* cur);
	bool remove(Key key, Node* parent, Node* cur);
	Node* del(Node* t, Node* t0);
	void print(Node* node, int lvl);
	void printKeys(Node* node);

public:
	Tree();
	Tree(Tree& t);
	~Tree();

	void clear();
	int getSize();
	bool isEmpty();
	bool insert(Key key, Data data);
	bool remove(Key key);
	Node* getNode(Key key);
	Data find(Key key);
	bool set(Key key, Data data);
	Node* min(Node* node);
	Node* max(Node* node);
	void print();
	void printKeys();
	int getSerialNumber(Key key);

	class Iterator {

	};

	class rIterator {

	};

	friend class Iterator;
	friend class rIterator;

	Iterator begin();
	Iterator end();

	rIterator rbegin();
	rIterator rend();
};

//-------------------Tree---------------------//

template <class Key, class Data>
Tree<Key, Data>::Tree() {
	this->size = 0;
	this->root = nullptr;
}

template <class Key, class Data>
Tree<Key, Data>::Tree(Tree<Key, Data>& t) {
	this->size = 0;
	this->root = nullptr;
	copyConstruct(t.root);
}

template <class Key, class Data>
Tree<Key, Data>::~Tree() {
	if (!this->isEmpty())
		this->clear();
}

template <class Key, class Data>
void Tree<Key, Data>::copy(Node* node) {
	insert(node->key, node->data);
	if (node->left)
		copy(node->left);
	if (node->right)
		copy(node->right);
}

template <class Key, class Data>
void Tree<Key, Data>::clear(Node* node) {
	if (node) {
		this->clear(node->left);
		this->clear(node->right);
		delete node;
		this->size--;
	}
}

template <class Key, class Data>
void Tree<Key, Data>::clear() {
	this->clear(this->root);
	this->root = nullptr;
	size = 0;
}

template <class Key, class Data>
int Tree<Key, Data>::getSize() {
	return this->size;
}

template <class Key, class Data>
bool Tree<Key, Data>::isEmpty() {
	return this->size == 0;
}

template <class Key, class Data>
bool Tree<Key, Data>::insert(Key key, Data data) {
	if (insert(key, data, nullptr, root)) {
		this->size++;
		return true;
	}
	else {
		return false;
	}
}

template <class Key, class Data>
bool Tree<Key, Data>::insert(Key key, Data data, Tree<Key, Data>::Node* parent, Tree<Key, Data>::Node* cur) {
	if (!cur && parent == nullptr)
		root = new Node(key, data);

	else if (!cur) {
		cur = new Node(key, data);
		key < parent->key ? parent->left = cur : parent->right = cur;
	}

	else {
		if (key < cur->key) {
			if (insert(key, data, cur, cur->left))
				cur->countSubNode++;
			else
				return false;
		}
		else if (key > cur->key) {
			if (insert(key, data, cur, cur->right))
				cur->countSubNode++;
			else
				return false;
		}
		else
			return false;
	}

	return true;
}

template <class Key, class Data>
bool Tree<Key, Data>::remove(Key key) {
	if (remove(key, nullptr, root)) {
		this->size--;
		return true;
	}
	else {
		return false;
	}
}

template <class Key, class Data>
bool Tree<Key, Data>::remove(Key key, Node* parent, Node* node) {

	return true;
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::del(Node* t, Node* t0) {
	if (t->left) {
		t->left = del(t->left, t0);
		return t;
	}

	t0->key = t->key;
	t0->data = t->data;

	Node* x = t->right;
	delete getNode(t->key);
	return x;
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::getNode(Key key) {
	return getNode(key, root);
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::getNode(Key key, Node* node) {
	if (!node)
		return nullptr;

	if (key == node->key)
		return node;
	else if (key < node->key)
		node = getNode(key, node->left);
	else
		node = getNode(key, node->right);
}

template <class Key, class Data>
Data Tree<Key, Data>::find(Key key) {
	Node* node = getNode(key);
	if (!node)
		throw TreeFindErr();

	return node->data;
}

template <class Key, class Data>
bool Tree<Key, Data>::set(Key key, Data data) {
	Node* node = getNode(key);

	if (!node)
		return false;

	node->data = data;
	return true;
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::min(Node* node) {
	if (!node)
		return nullptr;
	if (node->left)
		node = min(node->left);
	return node;
}

template <class Key, class Data>
typename Tree<Key, Data>::Node* Tree<Key, Data>::max(Node* node) {
	if (!node)
		return nullptr;
	if (node->right)
		node = max(node->right);
	return node;
}

template <class Key, class Data>
int Tree<Key, Data>::getSerialNumber(Key key) {
	if (!root)
		return -1;

	if (key == root->key)
		return root->left ? root->left->countSubNode : 0;

	int ans = 0;
	Node* node = root;
	
	while (node) {
		if (key == node->key) {
			return node->left ? ans + node->left->countSubNode : ans;
		}
		else if (key < node->key) {
			if (node->left)
				node = node->left;
			else
				return -1;
		}
		else {
			if (node->right) {
				if (node->left) {
					ans += node->left->countSubNode + 1;
					node = node->right;
				}
				else {
					ans += 1;
					node = node->right;
				}

			}
			else
				return -1;
		}
	}

	return -1;
}

template <class Key, class Data>
void Tree<Key, Data>::print() {
	print(root, 0);
}

template <class Key, class Data>
void Tree<Key, Data>::print(Node* node, int lvl) {
	if (!node)
		return;

	if (node->right)
		print(node->right, lvl + 1);
	for (int i = 0; i < lvl; i++)
		cout << "	";
	cout << node->key << endl;
	if (node->left)
		print(node->left, lvl + 1);
}

template <class Key, class Data>
void Tree<Key, Data>::printKeys() {
	printKeys(root);
}

template <class Key, class Data>
void Tree<Key, Data>::printKeys(Node* node) {
	if (!node)
		return;

	cout << node->key << " ";
	if (node->left)
		printKeys(node->left);
	if (node->right)
		printKeys(node->right);
}

//--------------------------------------------//
