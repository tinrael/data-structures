#pragma once

#include <cstddef>

template <typename T>
class Node
{
public:
	T key;

	bool mark;
	std::size_t degree;

	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	Node<T>* child;

	Node(T key);
};

template<typename T>
inline Node<T>::Node(T key) : 
	key(key), mark(false), degree(0), parent(nullptr), left(nullptr), right(nullptr), child(nullptr)
{
}
