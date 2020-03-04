#include "RedBlackTree.h"
#include <stdexcept>

RBTreeNode::RBTreeNode(int key) : key(key), color(COLOR_RED), parent(nullptr), left(nullptr), right(nullptr)
{
}

void RedBlackTree::insert(RBTreeNode* z)
{
	if (!z) {
		throw std::invalid_argument("The argument is nullptr.");
	}
	RBTreeNode* x = this->root;
	RBTreeNode* y = nullptr;
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

void RedBlackTree::rotateLeft(RBTreeNode* x)
{
	if (!x || !x->right) {
		return;
	}

	RBTreeNode* y = x->right;
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

void RedBlackTree::rotateRight(RBTreeNode* y)
{
	if (!y || !y->left) {
		return;
	}

	RBTreeNode* x = y->left;
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

void RedBlackTree::fixup(RBTreeNode* z)
{
	while (z->parent && z->parent->color == COLOR_RED) {
		if (z->parent == z->parent->parent->left) {
			RBTreeNode* y = z->parent->parent->right;
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
			RBTreeNode* y = z->parent->parent->left;
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

void RedBlackTree::print(const RBTreeNode* tree, std::ostream& out)
{
	if (!tree) {
		return;
	}
	print(tree->left, out);
	out << tree->key << " ";
	print(tree->right, out);
}

void RedBlackTree::deleteRBTreeNode(RBTreeNode* node)
{
	if (!node) {
		return;
	}
	deleteRBTreeNode(node->left);
	deleteRBTreeNode(node->right);
	delete node;
}

RedBlackTree::RedBlackTree() : root(nullptr)
{
}

RedBlackTree::~RedBlackTree()
{
	clear();
}

void RedBlackTree::insert(int key)
{
	RBTreeNode* newOne = new RBTreeNode(key);
	insert(newOne);
}

void RedBlackTree::print(std::ostream& out)
{
	print(this->root, out);
	out << std::endl;
}

void RedBlackTree::clear()
{
	deleteRBTreeNode(this->root);
	this->root = nullptr;
}