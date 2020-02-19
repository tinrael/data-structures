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
	inputFile.open("countries.dat", std::ios::binary | std::ios::in);
	if (!inputFile.is_open()) {
		std::cout << "Error. Failed to open the file." << std::endl;
		return 1;
	}

	std::vector<HashTableSlot<std::string, Country>*> slots;
	
	Country* newOne = nullptr;
	while (true) {
		newOne = new Country();
		if (newOne->load(inputFile)) {
			slots.push_back(new HashTableSlot<std::string, Country>(newOne->getName(), newOne));
		}
		else {
			delete newOne;
			break;
		}
	}

	inputFile.close();
	
	PerfectHashTable<std::string, Country>* table = new PerfectHashTable<std::string, Country>(slots);
	
	std::cout << "-----" << std::endl;
	std::cout << "| This application is using perfect hashing to store the static set of countries from the binary file 'countries.dat'." << std::endl;
	std::cout << "| The searching takes constant time O(1) in the worst case." << std::endl;
	std::cout << "-----" << std::endl;

	std::cout << "| The figure below represents the two levels of hashing." << std::endl;
	std::cout << "-----" << std::endl;
	
	table->printKeys();
	
	std::cout << "-----" << std::endl;
	std::cout << "| Searching: " << std::endl;
	std::cout << "-----" << std::endl;
	
	Country* country = nullptr;
	std::string name;
	for (std::size_t i = 0; i < 10; i++) {
		std::cout << "Enter the country to search: ";	
		std::cin >> name;

		country = table->search(name);
		
		std::cout << "-----" << std::endl;
		if (country) {
			std::cout << *country;
		}
		else {
			std::cout << "Not found." << std::endl;
		}
		std::cout << "-----" << std::endl;
	}

	for (HashTableSlot<std::string, Country>* slot : slots) {
		delete slot->getData();
		delete slot;
	}
	slots.clear();
	delete table;

	return 0;
}