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
	
	std::cout << "-----" << std::endl;
	std::cout << "| This application is using perfect hashing to store the static set of countries from the file 'countries.txt'." << std::endl;
	std::cout << "| The searching takes constant time O(1) in the worst case." << std::endl;
	std::cout << "-----" << std::endl;

	std::cout << "| The figure below represents the two levels of hashing." << std::endl;
	std::cout << "-----" << std::endl;
	
	table->printKeys();
	
	std::cout << "-----" << std::endl;
	std::cout << "| Searching: " << std::endl;
	std::cout << "-----" << std::endl;
	
	Country* country = nullptr;
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