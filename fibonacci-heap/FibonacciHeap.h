#pragma once

#include "Node.h"
#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
class FibonacciHeap
{
private:
	std::size_t numOfNodes; // number of nodes in the Fibonacci heap
	Node<T>* min;

	void link(Node<T> y, Node<T> x);

public:
	FibonacciHeap();
	
	void insert(T key);
	Node<T>* getMin();
	void print(std::ostream& out = std::cout);
};

template<typename T>
inline void FibonacciHeap<T>::link(Node<T> y, Node<T> x)
{
	if (!y || !x) {
		throw std::invalid_argument("nullptr argument(s) given");
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

template<typename T>
inline Node<T>* FibonacciHeap<T>::getMin()
{
	return min;
}

// TODO: print all nodes, not only root nodes
template<typename T>
inline void FibonacciHeap<T>::print(std::ostream& out)
{
	if (min) {
		Node<T>* cur = min;
		do {
			std::cout << cur->key;
			cur = cur->right;
			if (cur != min) {
				std::cout << " -> ";
			}
		} while (cur != min);
		std::cout << std::endl;
	}
	std::cout << "Number of nodes: " << numOfNodes << std::endl;
}
