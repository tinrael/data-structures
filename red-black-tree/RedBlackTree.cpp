#include "RedBlackTree.h"

RBTreeNode::RBTreeNode(int key) : key(key), color(COLOR_RED), parent(nullptr), left(nullptr), right(nullptr)
{
}

void RedBlackTree::insert(RBTreeNode*& tree, int key)
{
	if (!tree) {
		tree = new RBTreeNode(key);
	}
	else if (key < tree->key) {
		insert(tree->left, key);
	}
	else {
		insert(tree->right, key);
	}
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
	else if (y == y->parent->left) {
		y->parent->left = x;
	}
	else {
		y->parent->right = x;
	}
	x->right = y;
	y->parent = x;
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

// TODO: Fix up the red-black tree after insertion.
void RedBlackTree::insert(int key)
{
	insert(this->root, key);
}

void RedBlackTree::print(std::ostream& out)
{
	print(this->root, out);
}

void RedBlackTree::clear()
{
	deleteRBTreeNode(this->root);
	this->root = nullptr;
}