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

	std::vector<HashTableSlot<int, Country>*> slots;
	std::string name;
	std::string capital;
	unsigned population;
	double hdi;
	
	while (inputFile >> name >> capital >> population >> hdi) {
		slots.emplace_back(new HashTableSlot<int, Country>(population, new Country(name, capital, population, hdi)));
	}
	inputFile.close();
	
	PerfectHashTable<int, Country>* table = new PerfectHashTable<int, Country>(slots);
	table->printKeys();
	
	for (std::size_t i = 0; i < 10; i++) {
		std::cout << "Enter the population: ";
		std::cin >> population;
		Country* country = table->search(population);
		if (country) {
			std::cout << *country;
		}
		else {
			std::cout << "Not found." << std::endl;
		}
	}

	for (HashTableSlot<int, Country>* slot : slots) {
		delete slot->getData();
		delete slot;
	}
	delete table;

	return 0;
}