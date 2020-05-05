#pragma once

#include "Node.h"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>
#include <cmath>

template <typename T>
class FibonacciHeap
{
private:
	std::size_t numOfNodes; // number of nodes in the Fibonacci heap
	Node<T>* min;

	void consolidate();
	void link(Node<T>* y, Node<T>* x);
	
	void cut(Node<T>* x, Node<T>* y);

	void detachFromList(Node<T>* x); // detach the node from the doubly circularly-linked list
	void mergeLists(Node<T>* x, Node<T>* y); // merge two doubly circularly-linked lists together

public:
	FibonacciHeap();

	void insert(T key);
	Node<T>* extractMin(); // The heap loses ownership of the returned min node.
	Node<T>* getMin();
	void print(std::ostream& out = std::cout);
};

template<typename T>
inline void FibonacciHeap<T>::consolidate()
{
	if (!min) {
		return;
	}

	std::vector<Node<T>*> rootList;
	Node<T>* cur = min;
	do {
		rootList.push_back(cur); // Amortized constant complexity
		cur = cur->right;
	} while (cur != min);

	std::size_t size = (std::size_t)(std::log(numOfNodes) / std::log(1.5)) + 1; // floor[log(1.5, n)] + 1
	Node<T>** rootTable = new Node<T> * [size]();

	std::size_t d;
	Node<T>* y;
	for (Node<T>* x: rootList) {
		d = x->degree;
		while (rootTable[d]) {
			y = rootTable[d];
			if (x->key > y->key) {
				std::swap(x, y);
			}
			link(y, x);
			rootTable[d] = nullptr;
			d++;
		}
		rootTable[d] = x;

		if (x->key <= min->key) {
			min = x;
		}
	}

	delete[] rootTable;
}

template<typename T>
inline void FibonacciHeap<T>::link(Node<T>* y, Node<T>* x)
{
	if (!y || !x || (y == x)) {
		throw std::invalid_argument("nullptr pointer(s) or pointers to the same node are passed as argument(s)");
	}

	y->left->right = y->right;
	y->right->left = y->left;
	y->right = y;
	y->left = y;
	
	y->parent = x;
	if (x->child) {
		y->right = x->child;
		y->left = x->child->left;
		x->child->left->right = y;
		x->child->left = y;
	}
	else {
		x->child = y;
	}
	x->degree++;

	y->mark = false;
}

template<typename T>
inline void FibonacciHeap<T>::cut(Node<T>* x, Node<T>* y)
{
	if (!x || !y || (x == y)) {
		throw std::invalid_argument("nullptr pointer(s) or pointers to the same node are passed as argument(s)");
	}

	if (x == y->child) {
		if (x == x->right) {
			y->child = nullptr;
		}
		else {
			y->child = x->right;
		}
	}

	detachFromList(x);
	x->parent = nullptr;
	x->mark = false;
	y->degree--;
	mergeLists(min, x);
}

// This function detaches the node pointed by 'x' from the doubly circularly-linked list.
template<typename T>
inline void FibonacciHeap<T>::detachFromList(Node<T>* x)
{
	if (!x) {
		throw std::invalid_argument("nullptr is passed as argument");
	}

	x->left->right = x->right;
	x->right->left = x->left;
	x->right = x;
	x->left = x;
}

/* This function merges the two disjoint circularly-linked lists together into one circularly-linked list in O(1) time.
 * It merges y's nodes before x.
 */
template<typename T>
inline void FibonacciHeap<T>::mergeLists(Node<T>* x, Node<T>* y)
{
	if (!x || !y) {
		return;
	}

	Node<T>* xLeft = x->left;
	x->left = y->left;
	y->left->right = x;
	xLeft->right = y;
	y->left = xLeft;
}

template<typename T>
inline FibonacciHeap<T>::FibonacciHeap() : numOfNodes(0), min(nullptr)
{
}

template<typename T>
inline void FibonacciHeap<T>::insert(T key)
{
	// The Fibonacci heap takes ownership of x.
	Node<T>* x = new Node<T>(key);
	if (!min) {
		min = x;
	}
	else {
		x->right = min;
		x->left = min->left;
		min->left->right = x;
		min->left = x;
		
		if (x->key < min->key) {
			min = x;
		}
	}
	numOfNodes++;
}

// The heap loses ownership of the returned min node 'z'.
template<typename T>
inline Node<T>* FibonacciHeap<T>::extractMin()
{
	Node<T>* z = min;
	if (z) {
		if (z->child) {
			Node<T>* cur = z->child;
			do {
				cur->parent = nullptr;
				cur = cur->right;
			} while (cur != z->child);
			mergeLists(z, z->child);
		}
		z->left->right = z->right;
		z->right->left = z->left;
		if (z == z->right) {
			min = nullptr;
		}
		else {
			min = z->right;
			consolidate();
		}
		numOfNodes--;
	}
	return z;
}

template<typename T>
inline Node<T>* FibonacciHeap<T>::getMin()
{
	return min;
}

// TODO: print all nodes
template<typename T>
inline void FibonacciHeap<T>::print(std::ostream& out)
{
	if (min) {
		Node<T>* curRoot = min;
		do {
			std::cout << curRoot->key << std::endl;

			if (curRoot->child) {
				Node<T>* curChild = curRoot->child;
				do {
					std::cout << curChild->key;
					curChild = curChild->right;
					if (curChild != curRoot->child) {
						std::cout << " -> ";
					}
				} while (curChild != curRoot->child);
				std::cout << std::endl;
			}

			std::cout << " --- \t --- " << std::endl;		
			curRoot = curRoot->right;
		} while (curRoot != min);
	}
	std::cout << "Number of nodes: " << numOfNodes << std::endl;
}
