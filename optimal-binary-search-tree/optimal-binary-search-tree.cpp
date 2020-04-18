#include "OptimalBinarySearchTree.h"
#include "sqlite3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	if (argv[0]) {
		std::vector<std::string>* keys = static_cast<std::vector<std::string>*>(NotUsed);
		keys->push_back(argv[0]);
	}
	return 0;
}

int main()
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc = sqlite3_open("countries.db", &db);
	if (rc) {
		std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return(1);
	}

	std::ofstream outputFile("graph1.gv");
	if (!outputFile.is_open()) {
		std::cout << "Unable to open file." << std::endl;
		return 1;
	}

	// TODO: check all corner cases (in particular, select limit 0). Refactor the code.
	const char* sql = "select name from country order by name asc limit 5;";
	std::vector<std::string> keys;
	double probabilities[] = { 0.05, 0.3, 0.15, 0.2, 0.3 };

	rc = sqlite3_exec(db, sql, callback, &keys, &zErrMsg);
	if (rc != SQLITE_OK) {
		std::cout << "SQL error: " << zErrMsg << std::endl;
		sqlite3_free(zErrMsg);
	}
	else {
		OptimalBinarySearchTree<std::string> tree(&keys[0], probabilities, keys.size());
		std::cout << "Expected cost of searching an optimal BST: " << tree.getExpectedSearchCost() << std::endl;
		// Prints the tree in the DOT language to the graph1.gv file.
		tree.printDotLanguage(outputFile);
	}

	outputFile.close();
	sqlite3_close(db);

	return 0;
}