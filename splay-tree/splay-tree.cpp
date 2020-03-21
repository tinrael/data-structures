#include "SplayTree.h"
#include <iostream>
#include <fstream>

int main()
{
	std::ofstream outputFile("graph1.gv");
	if (!outputFile.is_open()) {
		std::cout << "Unable to open file." << std::endl;
		return 1;
	}

	SplayTree<int> tree;
	tree.insert(6);
	tree.insert(8);
	tree.insert(10);
	tree.insert(19);
	tree.insert(15);
	tree.insert(13);
	tree.insert(2);
	tree.insert(7);
	tree.insert(12);
	tree.insert(5);
	
	tree.erase(50);
	tree.erase(25);
	tree.erase(19);
	tree.erase(8);
	
	tree.print();
	// Prints the tree in the DOT language to the graph1.gv file.
	tree.printDotLanguage(outputFile);
}