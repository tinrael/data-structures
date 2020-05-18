#pragma once

#include "RBTreeNode.h"
#include <iostream>
#include <stdexcept>

template <typename KeyType>
class RedBlackTree
{
private:
	RBTreeNode<KeyType>* root;

	void fixup(RBTreeNode<KeyType>* z);
	void rotateLeft(RBTreeNode<KeyType>* x);
	void rotateRight(RBTreeNode<KeyType>* y);

	// Prints the tree according to the inorder traversal.
	void print(const RBTreeNode<KeyType>* tree, std::ostream& out);
	void deleteRBTreeNode(RBTreeNode<KeyType>* node);

	void printDotVertices(RBTreeNode<KeyType>* tree, std::ostream& out);
	void printDotEdges(RBTreeNode<KeyType>* tree, std::ostream& out);

public:
	RedBlackTree();
	~RedBlackTree();

	void insert(KeyType key);
	// Returns the pointer to the node with the key 'key'.
	RBTreeNode<KeyType>* search(KeyType key);
	// Prints the tree according to the inorder traversal.
	void print(std::ostream& out = std::cout);
	// Deletes all nodes.
	void clear();

	// Prints the tree in the DOT language.
	void printDotLanguage(std::ostream& out = std::cout);
};

template <typename KeyType>
inline void RedBlackTree<KeyType>::fixup(RBTreeNode<KeyType>* z)
{
	if (!z) {
		throw std::invalid_argument("The argument z is nullptr.");
	}
	while (z->parent && z->parent->color == COLOR_RED) {
		if (z->parent == z->parent->parent->left) {
			RBTreeNode<KeyType>* y = z->parent->parent->right;
			if (y && y->color == COLOR_RED) {
				z->parent->color = COLOR_BLACK;
				y->color = COLOR_BLACK;
				z->parent->parent->color = COLOR_RED;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					rotateLeft(z);
				}
				z->parent->color = COLOR_BLACK;
				z->parent->parent->color = COLOR_RED;
				rotateRight(z->parent->parent);
			}
		}
		else {
			RBTreeNode<KeyType>* y = z->parent->parent->left;
			if (y && y->color == COLOR_RED) {
				z->parent->color = COLOR_BLACK;
				y->color = COLOR_BLACK;
				z->parent->parent->color = COLOR_RED;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					rotateRight(z);
				}
				z->parent->color = COLOR_BLACK;
				z->parent->parent->color = COLOR_RED;
				rotateLeft(z->parent->parent);
			}
		}
	}
	this->root->color = COLOR_BLACK;
}

template<typename KeyType>
inline void RedBlackTree<KeyType>::rotateLeft(RBTreeNode<KeyType>* x)
{
	if (!x || !x->right) {
		return;
	}

	RBTreeNode<KeyType>* y = x->right;
	x->right = y->left;
	if (y->left) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (!x->parent) {
		this->root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

template<typename KeyType>
inline void RedBlackTree<KeyType>::rotateRight(RBTreeNode<KeyType>* y)
{
	if (!y || !y->left) {
		return;
	}

	RBTreeNode<KeyType>* x = y->left;
	y->left = x->right;
	if (x->right) {
		x->right->parent = y;
	}
	x->parent = y->parent;
	if (!y->parent) {
		this->root = x;
	}
	else if (y == y->parent->right) {
		y->parent->right = x;
	}
	else {
		y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
}

template<typename KeyType>
inline void RedBlackTree<KeyType>::print(const RBTreeNode<KeyType>* tree, std::ostream& out)
{
	if (!tree) {
		return;
	}
	print(tree->left, out);
	out << tree->key << " ";
	print(tree->right, out);
}

template<typename KeyType>
inline void RedBlackTree<KeyType>::deleteRBTreeNode(RBTreeNode<KeyType>* node)
{
	if (!node) {
		return;
	}
	deleteRBTreeNode(node->left);
	deleteRBTreeNode(node->right);
	delete node;
}

template<typename KeyType>
inline void RedBlackTree<KeyType>::printDotVertices(RBTreeNode<KeyType>* tree, std::ostream& out)
{
	if (!tree) {
		return;
	}
	out << tree->id << " [label=\"" << tree->key;
	switch (tree->color) {
	case COLOR_BLACK:
		out << "\", fillcolor=black]" << std::endl;
		break;
	case COLOR_RED:
		out << "\", fillcolor=red]" << std::endl;
		break;
	default:
		out << "\"]" << std::endl;
		break;
	}
	printDotVertices(tree->left, out);
	if (tree->left || tree->right) {
		out << "invis" << tree->id << " [label=\"\", width=.8, style=invis]" << std::endl;
	}
	printDotVertices(tree->right, out);
}

template<typename KeyType>
inline void RedBlackTree<KeyType>::printDotEdges(RBTreeNode<KeyType>* tree, std::ostream& out)
{
	if (!tree) {
		return;
	}
	if (tree->left) {
		out << tree->id << " -> ";
		printDotEdges(tree->left, out);
	}
	if (tree->right) {
		out << tree->id << " -> ";
		printDotEdges(tree->right, out);
	}
	if (!tree->right && !tree->left) {
		out << tree->id << std::endl;
	}
	else {
		out << tree->id << " -> " << "invis" << tree->id << " [style=invis]" << std::endl;
	}
}

template<typename KeyType>
inline RedBlackTree<KeyType>::RedBlackTree() : root(nullptr)
{
}

template<typename KeyType>
inline RedBlackTree<KeyType>::~RedBlackTree()
{
	clear();
}

template<typename KeyType>
inline void RedBlackTree<KeyType>::insert(KeyType key)
{
	// The red-black tree takes ownership of z.
	RBTreeNode<KeyType>* z = new RBTreeNode<KeyType>(key);
	RBTreeNode<KeyType>* x = this->root;
	RBTreeNode<KeyType>* y = nullptr;
	while (x) {
		y = x;
		if (z->key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	z->parent = y;
	if (!y) {
		this->root = z;
	}
	else if (z->key < y->key) {
		y->left = z;
	}
	else {
		y->right = z;
	}
	fixup(z);
}

template<typename KeyType>
inline RBTreeNode<KeyType>* RedBlackTree<KeyType>::search(KeyType key)
{
	RBTreeNode<KeyType>* x = this->root;
	while (x && (key != x->key)) {
		if (key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	return x;
}

template<typename KeyType>
inline void RedBlackTree<KeyType>::print(std::ostream& out)
{
	print(this->root, out);
	out << std::endl;
}

template<typename KeyType>
inline void RedBlackTree<KeyType>::printDotLanguage(std::ostream& out)
{
	if (!this->root) {
		return;
	}
	out << "digraph G {" << std::endl;
	out << "node[style=filled, fontname=Helvetica, fontcolor=white, fontsize=20]" << std::endl;
	printDotVertices(this->root, out);
	printDotEdges(this->root, out);
	out << "}" << std::endl;
}

template<typename KeyType>
inline void RedBlackTree<KeyType>::clear()
{
	deleteRBTreeNode(this->root);
	this->root = nullptr;
}
