#include "PersistentRBTree.h"
#include "sqlite3.h"
#include <iostream>
#include <fstream>
#include <string>

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	if (argv[0]) {
		PersistentRBTree<std::string>* tree = static_cast<PersistentRBTree<std::string>*>(NotUsed);
		tree->insert(argv[0]);
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

	PersistentRBTree<std::string> tree;
	const char* sql = "select name from country;";

	rc = sqlite3_exec(db, sql, callback, &tree, &zErrMsg);
	if (rc != SQLITE_OK) {
		std::cout << "SQL error: " << zErrMsg << std::endl;
		sqlite3_free(zErrMsg);
	}

	tree.print();
	// Prints the tree in the DOT language to the graph1.gv file.
	tree.printDotLanguage(outputFile);

	outputFile.close();
	sqlite3_close(db);

	return 0;
}
