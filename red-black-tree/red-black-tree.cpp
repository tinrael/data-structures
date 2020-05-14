#include "RedBlackTree.h"
#include <iostream>
#include <fstream>

int main()
{
	std::ofstream outputFile("graph1.gv");
	if (!outputFile.is_open()) {
		std::cout << "Unable to open file." << std::endl;
		return 1;
	}

	RedBlackTree<int> tree;
	tree.insert(6);
	tree.insert(17);
	tree.insert(34);
	tree.insert(56);
	tree.insert(112);
	tree.insert(2);
	tree.insert(1);
	tree.insert(9);
	tree.print();

	// Prints the tree in the DOT language to the graph1.gv file.
	tree.printDotLanguage(outputFile);
}