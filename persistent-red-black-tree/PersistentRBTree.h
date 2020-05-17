#pragma once

#include "RBTreeNode.h"
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <vector>

template <typename KeyType>
class PersistentRBTree
{
private:
	void fixup(RBTreeNode<KeyType>* z);
	void rotateLeft(RBTreeNode<KeyType>* x);
	void rotateRight(RBTreeNode<KeyType>* y);

	// Prints the tree according to the inorder traversal.
	void print(const RBTreeNode<KeyType>* tree, std::ostream& out);
	void deleteRBTreeNode(RBTreeNode<KeyType>* node);

	void printDotVertices(RBTreeNode<KeyType>* tree, std::ostream& out);
	void printDotEdges(RBTreeNode<KeyType>* tree, std::ostream& out);

public:
	std::vector<RBTreeNode<KeyType>*> roots;
	std::size_t current;
	std::size_t next;

	PersistentRBTree();
	~PersistentRBTree();

	void insert(KeyType key);
	
	// Cancels the last operation.
	void undo();
	// Reverses the undo operation.
	void redo();
	
	// Prints the tree according to the inorder traversal.
	void print(std::ostream& out = std::cout);
	// Deletes all nodes.
	void clear();

	// Prints the tree in the DOT language.
	void printDotLanguage(std::ostream& out = std::cout);
};

template <typename KeyType>
inline void PersistentRBTree<KeyType>::fixup(RBTreeNode<KeyType>* z)
{
	if (!z) {
		throw std::invalid_argument("The argument z is nullptr.");
	}
	while (z->parent && z->parent->color == COLOR_RED) {
		if (z->parent == z->parent->parent->left) {
			RBTreeNode<KeyType>* y = z->parent->parent->right;
			if (y && y->color == COLOR_RED) {
				z->parent->parent->right = new RBTreeNode<KeyType>(*y);
				y = z->parent->parent->right;
				y->parent = z->parent->parent;

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
				z->parent->parent->left = new RBTreeNode<KeyType>(*y);
				y = z->parent->parent->left;
				y->parent = z->parent->parent;

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
	roots[current]->color = COLOR_BLACK;
}

template<typename KeyType>
inline void PersistentRBTree<KeyType>::rotateLeft(RBTreeNode<KeyType>* x)
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
		roots[current] = y;
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
inline void PersistentRBTree<KeyType>::rotateRight(RBTreeNode<KeyType>* y)
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
		roots[current] = x;
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
inline void PersistentRBTree<KeyType>::print(const RBTreeNode<KeyType>* tree, std::ostream& out)
{
	if (!tree) {
		return;
	}
	print(tree->left, out);
	out << tree->key << " ";
	print(tree->right, out);
}

template<typename KeyType>
inline void PersistentRBTree<KeyType>::deleteRBTreeNode(RBTreeNode<KeyType>* node)
{
	if (!node) {
		return;
	}
	deleteRBTreeNode(node->left);
	deleteRBTreeNode(node->right);
	delete node;
}

template<typename KeyType>
inline void PersistentRBTree<KeyType>::printDotVertices(RBTreeNode<KeyType>* tree, std::ostream& out)
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
inline void PersistentRBTree<KeyType>::printDotEdges(RBTreeNode<KeyType>* tree, std::ostream& out)
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
inline PersistentRBTree<KeyType>::PersistentRBTree() : roots(2), current(0), next(1)
{
}

// TODO: This operation works incorrectly. Need to use smart pointers.
template<typename KeyType>
inline PersistentRBTree<KeyType>::~PersistentRBTree()
{
	clear();
}

template<typename KeyType>
inline void PersistentRBTree<KeyType>::insert(KeyType key)
{
	// The red-black tree takes ownership of z.
	RBTreeNode<KeyType>* z = new RBTreeNode<KeyType>(key);

	RBTreeNode<KeyType>* x = roots[current];
	RBTreeNode<KeyType>** y = &roots[next];
	RBTreeNode<KeyType>* p = nullptr;

	while (x) {
		*y = new RBTreeNode<KeyType>(*x);
		(*y)->parent = p;
		if (z->key < x->key) {
			x = x->left;
			p = *y;
			y = &((*y)->left);
		}
		else {
			x = x->right;
			p = *y;
			y = &((*y)->right);
		}
	}
	z->parent = p;
	*y = z;

	current = next;
	next++;

	fixup(z);

	std::size_t size = roots.size();
	if (next == size) {
		roots.resize(2 * size);
	}
	roots[next] = nullptr;
}

template<typename KeyType>
inline void PersistentRBTree<KeyType>::undo()
{
	if (current) {
		next = current;
		current--;
	}
}

template<typename KeyType>
inline void PersistentRBTree<KeyType>::redo()
{
	if (roots[next]) {
		current = next;
		next++;
	}
}

template<typename KeyType>
inline void PersistentRBTree<KeyType>::print(std::ostream& out)
{
	print(roots[current], out);
	out << std::endl;
}

template<typename KeyType>
inline void PersistentRBTree<KeyType>::printDotLanguage(std::ostream& out)
{
	if (!roots[current]) {
		return;
	}
	out << "digraph G {" << std::endl;
	out << "node[style=filled, fontname=Helvetica, fontcolor=white, fontsize=20]" << std::endl;
	printDotVertices(roots[current], out);
	printDotEdges(roots[current], out);
	out << "}" << std::endl;
}

// TODO: This operation works incorrectly. Need to use smart pointers.
template<typename KeyType>
inline void PersistentRBTree<KeyType>::clear()
{
	deleteRBTreeNode(roots[current]);
	roots[current] = nullptr;
}
