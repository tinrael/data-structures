#pragma once

#include <cstddef>

enum Color {
	COLOR_RED,
	COLOR_BLACK
};

// Red-black Tree Node
template <typename KeyType>
class RBTreeNode {
public:
	static std::size_t idGenerator;
	std::size_t id;

	KeyType key;
	Color color;

	RBTreeNode<KeyType>* parent;
	RBTreeNode<KeyType>* left;
	RBTreeNode<KeyType>* right;

	RBTreeNode(KeyType key);
};

template <typename KeyType>
std::size_t RBTreeNode<KeyType>::idGenerator = 0;

template <typename KeyType>
inline RBTreeNode<KeyType>::RBTreeNode(KeyType key)
	: id(idGenerator),
	key(key),
	color(COLOR_RED),
	parent(nullptr),
	left(nullptr),
	right(nullptr)
{
	idGenerator++;
}
