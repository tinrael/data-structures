#pragma once

#include "Node.h"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>
#include <cmath>
#include <string>

template <typename T>
class FibonacciHeap
{
private:
	std::size_t numOfNodes; // number of nodes in the Fibonacci heap
	Node<T>* min;

	void consolidate();
	void link(Node<T>* y, Node<T>* x);
	
	void cut(Node<T>* x, Node<T>* y);
	void cascadingCut(Node<T>* y);

	Node<T>* find(Node<T>* heap, T key);
	void deleteHeap(Node<T>* heap);

	void printVerticesInDot(Node<T>* heap, std::ostream& out = std::cout);
	void printEdgesInDot(Node<T>* heap, std::ostream& out = std::cout);

	void detachFromList(Node<T>* x); // detach the node from the doubly circularly-linked list
	void mergeLists(Node<T>* x, Node<T>* y); // merge two doubly circularly-linked lists together

public:
	FibonacciHeap();
	~FibonacciHeap();

	void insert(T key);
	void erase(Node<T>* x);
	void erase(T key);
	Node<T>* find(T key);
	void decreaseKey(Node<T>* x, T newValue);
	void decreaseKey(T oldValue, T newValue);
	Node<T>* extractMin(); // The heap loses ownership of the returned min node.
	Node<T>* getMin();
	
	void clear();
	void print(std::ostream& out = std::cout);
	// Prints the heap in the DOT language.
	void printInDot(std::ostream& out = std::cout); // Single-responsibility principle? Refactor the code.
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
	
	detachFromList(y);
	y->parent = x;
	if (x->child) {
		mergeLists(x->child, y);
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

template<typename T>
inline void FibonacciHeap<T>::cascadingCut(Node<T>* y)
{
	if (!y) {
		throw std::invalid_argument("nullptr is passed as argument");
	}

	Node<T>* z = y->parent;
	if (z) {
		if (y->mark == false) {
			y->mark = true;
		}
		else {
			cut(y, z);
			cascadingCut(z);
		}
	}
}

template<typename T>
inline Node<T>* FibonacciHeap<T>::find(Node<T>* heap, T key)
{
	if (heap) {
		Node<T>* cur = heap;
		Node<T>* found = nullptr;

		do {
			if (std::abs(key - cur->key) <= std::numeric_limits<T>::epsilon()) {
				return cur;
			}
			if (key > cur->key) {
				found = find(cur->child, key);
				if (found) {
					return found;
				}
			}

			cur = cur->right;
		} while (cur != heap);
	}
	return nullptr;
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
inline void FibonacciHeap<T>::deleteHeap(Node<T>* heap)
{
	if (!heap) {
		return;
	}

	Node<T>* cur = heap;
	Node<T>* last = heap->left;
	Node<T>* toDelete;
	while (cur != last) {
		deleteHeap(cur->child);
		toDelete = cur;
		cur = cur->right;
		delete toDelete;
	}
	deleteHeap(last->child);
	delete last;
}

template<typename T>
inline void FibonacciHeap<T>::printVerticesInDot(Node<T>* heap, std::ostream& out)
{
	if (!heap) {
		return;
	}

	Node<T>* cur = heap;
	do {
		if (cur->mark == true) {
			out << cur->key << " [fillcolor=red, fontcolor=white];" << std::endl;
		}
		printVerticesInDot(cur->child, out);
		
		cur = cur->right;
	} while (cur != heap);
}

/* Not stable version.
 * TODO BUG: insert in a heap 50 numbers from 1 to 50 [1...50].
 * Then extractMin(), erase(6), erase(12), erase(25) (in this order). Print in dot. Look at nodes 24-22-23 (bug here).
 * Disable printVerticesIndot(). Look at nodes 24-22-23 again (one more bug here).
 * The attributes of nodes 24 and 23 are correct.
 * TODO: more tests.
 * TODO: does not correctly visualize the heap with double values. Insert in an empty heap any double (0.41). Print in dot.
 * You'll get: 0.41; { rank=same; 0.410000;  }
 */
template<typename T>
inline void FibonacciHeap<T>::printEdgesInDot(Node<T>* heap, std::ostream& out)
{
	if (!heap) {
		return;
	}

	std::string rank = "{ rank=same; ";
	
	Node<T>* cur = heap;
	do {
		if (cur->child) {
			out << cur->key << " -- ";
			printEdgesInDot(cur->child, out);
		}
		if (cur->parent && (cur != cur->parent->child)) {
			out << cur->parent->key << " -- " << cur->key << std::endl;
		}
		if (cur->right != heap) {
			out << cur->key << " -- ";
		}
		else if (!cur->child) {
			out << cur->key << ";" << std::endl;
		}

		rank += std::to_string(cur->key) + "; ";

		cur = cur->right;
	} while (cur != heap);

	rank += " }";
	out << rank << std::endl;
}

template<typename T>
inline FibonacciHeap<T>::FibonacciHeap() : numOfNodes(0), min(nullptr)
{
}

template<typename T>
inline FibonacciHeap<T>::~FibonacciHeap()
{
	deleteHeap(min);
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
		mergeLists(min, x);
		if (x->key < min->key) {
			min = x;
		}
	}
	numOfNodes++;
}

template<typename T>
inline void FibonacciHeap<T>::erase(Node<T>* x)
{
	if (!x) {
		throw std::invalid_argument("The nullptr is passed as the argument 'x'.");
	}

	decreaseKey(x, std::numeric_limits<T>::lowest());
	Node<T>* toDelete = extractMin();
	delete toDelete;
}

template<typename T>
inline void FibonacciHeap<T>::erase(T key)
{
	Node<T>* found = find(key);
	if (found) {
		erase(found);
	}
}

template<typename T>
inline Node<T>* FibonacciHeap<T>::find(T key)
{
	return find(min, key);
}

template<typename T>
inline void FibonacciHeap<T>::decreaseKey(Node<T>* x, T newValue)
{
	if (!x) {
		throw std::invalid_argument("The nullptr is passed as the argument 'x'.");
	}
	else if (newValue > x->key) {
		throw std::invalid_argument("The new key is bigger than the current key.");
	}
	
	x->key = newValue;
	Node<T>* y = x->parent;
	if (y && (x->key < y->key)) {
		cut(x, y);
		cascadingCut(y);
	}
	if (x->key < min->key) {
		min = x;
	}
}

template<typename T>
inline void FibonacciHeap<T>::decreaseKey(T oldValue, T newValue)
{
	Node<T>* found = find(oldValue);
	if (found) {
		decreaseKey(found, newValue);
	}
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

template<typename T>
inline void FibonacciHeap<T>::clear()
{
	deleteHeap(min);
	min = nullptr;
	numOfNodes = 0;
}

// TODO: print all nodes
template<typename T>
inline void FibonacciHeap<T>::print(std::ostream& out)
{
	if (min) {
		Node<T>* curRoot = min;
		do {
			out << curRoot->key << std::endl;

			if (curRoot->child) {
				Node<T>* curChild = curRoot->child;
				do {
					out << curChild->key;
					curChild = curChild->right;
					if (curChild != curRoot->child) {
						out << " -> ";
					}
				} while (curChild != curRoot->child);
				out << std::endl;
			}

			out << " --- \t --- " << std::endl;
			curRoot = curRoot->right;
		} while (curRoot != min);
	}
	out << "Number of nodes: " << numOfNodes << std::endl;
}

// Single-responsibility principle? Refactor the code.
template<typename T>
inline void FibonacciHeap<T>::printInDot(std::ostream& out)
{
	if (!min) {
		return;
	}

	out << "graph G {" << std::endl;
	out << "node[style=filled, fillcolor=lightblue, fontname=Helvetica, fontsize=15]" << std::endl;
	out << "graph[nodesep = .5];" << std::endl;
	printVerticesInDot(min, out);
	printEdgesInDot(min, out);
	out << "}" << std::endl;
}
