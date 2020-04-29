#pragma once

#include "Node.h"
#include <cstddef>

template <typename T>
class FibonacciHeap
{
private:
	std::size_t n; // number of nodes in the Fibonacci heap
	Node<T>* min;

public:
	FibonacciHeap();

};

template<typename T>
inline FibonacciHeap<T>::FibonacciHeap() : n(0), min(nullptr)
{
}
