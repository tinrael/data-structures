#pragma once

#include "Node.h"
#include <cstddef>
#include <iostream>

template <typename T>
class FibonacciHeap
{
private:
	std::size_t numOfNodes; // number of nodes in the Fibonacci heap
	Node<T>* min;

public:
	FibonacciHeap();
	
	void insert(T key);
	Node<T>* getMin();
	void print(std::ostream& out = std::cout);
};

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
