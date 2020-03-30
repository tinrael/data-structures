#include "OptimalBinarySearchTree.h"

#include <iostream>
#include <fstream>
#include <cstddef>

int main()
{
	std::ofstream outputFile("graph1.gv");
	if (!outputFile.is_open()) {
		std::cout << "Unable to open file." << std::endl;
		return 1;
	}

	int keys[] = { 10, 14, 17, 20 };
	double probabilities[] = { 0.3, 0.1, 0.4, 0.2 };
	std::size_t size = sizeof(keys) / sizeof(keys[0]);

	OptimalBinarySearchTree<int> tree(keys, probabilities, size);

	std::cout << "Expected cost of searching an optimal BST: " << tree.getExpectedSearchCost() << std::endl;
 
	// Prints the tree in the DOT language to the graph1.gv file.
	tree.printDotLanguage(outputFile);
}