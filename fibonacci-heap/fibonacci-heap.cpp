#include "FibonacciHeap.h"
#include "sqlite3.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	if (argv[0]) {
		FibonacciHeap<int>* heap = static_cast<FibonacciHeap<int>*>(NotUsed);
		heap->insert(std::atoi(argv[0]));
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

	FibonacciHeap<int> heap;
	const char* sql = "select population from country limit 15;";

	rc = sqlite3_exec(db, sql, callback, &heap, &zErrMsg);
	if (rc != SQLITE_OK) {
		std::cout << "SQL error: " << zErrMsg << std::endl;
		sqlite3_free(zErrMsg);
	}

	delete heap.extractMin();

	// Prints the Fibonacci heap in the DOT language to the graph1.gv file.
	heap.printInDot(outputFile);

	outputFile.close();
	sqlite3_close(db);

	return 0;
}