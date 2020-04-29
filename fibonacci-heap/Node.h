#pragma once

#include <cstddef>

template <typename T>
class Node
{
public:
	bool mark;
	std::size_t degree;

	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	Node<T>* child;

	Node();
};

template<typename T>
inline Node<T>::Node() : 
	mark(false), degree(0), parent(nullptr), left(nullptr), right(nullptr), child(nullptr)
{
}
