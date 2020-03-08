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
	static std::size_t idGenerator;
	std::size_t id;
	
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

	void fixup(RBTreeNode* z);
	void rotateLeft(RBTreeNode* x);
	void rotateRight(RBTreeNode* y);

	// Prints the tree according to the inorder traversal.
	void print(const RBTreeNode* tree, std::ostream& out);
	void deleteRBTreeNode(RBTreeNode* node);

	void printDotVertices(RBTreeNode* tree, std::ostream& out);
	void printDotEdges(RBTreeNode* tree, std::ostream& out);

public:
	RedBlackTree();
	~RedBlackTree();

	void insert(int key);
	// Prints the tree according to the inorder traversal.
	void print(std::ostream& out = std::cout);
	// Deletes all nodes.
	void clear();

	// Prints the tree in the DOT language.
	void printDotLanguage(std::ostream& out = std::cout);
};