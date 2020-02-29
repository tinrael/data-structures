#pragma once

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

public:
	RedBlackTree();

	void insert(int key);
};

