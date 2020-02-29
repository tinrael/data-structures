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
};

