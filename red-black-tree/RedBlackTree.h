#pragma once

#include <iostream>

enum Color {
	COLOR_RED,
	COLOR_BLACK
};

// Red-black Tree Node
class RBTreeNode {
public:
	int key;
	Color color;

	RBTreeNode* parent;
	RBTreeNode* left;
	RBTreeNode* right;

	RBTreeNode(int key);
};

class RedBlackTree
{
private:
	RBTreeNode* root;

	void insert(RBTreeNode*& tree, int key);
	void rotateLeft(RBTreeNode* x);
	void rotateRight(RBTreeNode* y);

	// Prints the tree according to the inorder traversal.
	void print(const RBTreeNode* tree, std::ostream& out);

public:
	RedBlackTree();

	void insert(int key);
	// Prints the tree according to the inorder traversal.
	void print(std::ostream& out = std::cout);
};