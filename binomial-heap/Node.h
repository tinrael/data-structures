#pragma once

#include <cstddef>

template <typename KeyType>
class Node
{
public:
	KeyType key;

	std::size_t degree;
	Node<KeyType>* parent;
	Node<KeyType>* child;
	Node<KeyType>* sibling;

	Node(KeyType key);

};

template<typename KeyType>
inline Node<KeyType>::Node(KeyType key)
	: key{ key }, degree{ 0 }, parent{ nullptr }, child{ nullptr }, sibling{ nullptr }
{
}
