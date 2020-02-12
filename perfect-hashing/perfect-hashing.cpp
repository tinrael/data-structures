#include "Country.h"
#include "PerfectHashTable.h"
#include "HashTableSlot.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstddef>

int main()
{
	std::ifstream inputFile;
	inputFile.open("countries.txt");
	
	if (!inputFile.is_open()) {
		std::cout << "Error. Failed to open the file." << std::endl;
		return 1;
	}

	std::vector<HashTableSlot<std::string, Country>*> slots;
	std::string name;
	std::string capital;
	unsigned population;
	double hdi;
	
	while (inputFile >> name >> capital >> population >> hdi) {
		slots.emplace_back(new HashTableSlot<std::string, Country>(name, new Country(name, capital, population, hdi)));
	}
	inputFile.close();
	
	PerfectHashTable<std::string, Country>* table = new PerfectHashTable<std::string, Country>(slots);
	table->printKeys();
	
	for (std::size_t i = 0; i < 10; i++) {
		std::cout << "Enter the country: ";
		std::cin >> name;
		Country* country = table->search(name);
		if (country) {
			std::cout << *country;
		}
		else {
			std::cout << "Not found." << std::endl;
		}
	}

	for (HashTableSlot<std::string, Country>* slot : slots) {
		delete slot->getData();
		delete slot;
	}
	delete table;

	return 0;
}