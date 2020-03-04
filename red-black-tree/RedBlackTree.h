#pragma once

#include <iostream>
#include <cstddef>

enum Color {
	COLOR_RED,
	COLOR_BLACK
};

// Red-black Tree Node
class RBTreeNode {
public:
	std::size_t id;
	static std::size_t idGenerator;
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

	void rotateLeft(RBTreeNode* x);
	void rotateRight(RBTreeNode* y);
	void fixup(RBTreeNode* z);

	// Prints the tree according to the inorder traversal.
	void print(const RBTreeNode* tree, std::ostream& out);
	void deleteRBTreeNode(RBTreeNode* node);

public:
	RedBlackTree();
	~RedBlackTree();

	void insert(int key);
	// Prints the tree according to the inorder traversal.
	void print(std::ostream& out = std::cout);
	// Deletes all nodes.
	void clear();
};