#pragma once

#include "HashTable.h"
#include "HashFunction.h"
#include "HashTableSlot.h"
#include <cstddef>
#include <vector>
#include <stdexcept>
#include <iostream>

template<typename KeyType, typename DataType>
class PerfectHashTable
{
private:
	HashTable<KeyType, DataType>** primaryTable;
	std::size_t size;

	HashFunction hashFunction;

	void insert(const std::vector<HashTableSlot<KeyType, DataType>*>& slots);

public:
	PerfectHashTable(const std::vector<HashTableSlot<KeyType, DataType>*>& slots);
	~PerfectHashTable();

	DataType* search(KeyType key);
	void printKeys();
};

template<typename KeyType, typename DataType>
inline void PerfectHashTable<KeyType, DataType>::insert(const std::vector<HashTableSlot<KeyType, DataType>*>& slots)
{
	std::vector<std::vector<HashTableSlot<KeyType, DataType>*>> buckets(size);
	
	for (HashTableSlot<KeyType, DataType>* slot : slots) {
		if (!slot || !slot->getData()) {
			throw std::invalid_argument("The slots argument is incorrect.");
		}
		std::size_t index = hashFunction.getHashValue(slot->getKey());
		buckets[index].push_back(slot);
	}

	// Inserts each bucket to the appropriate secondary hash table.
	std::size_t i = 0;
	for (const std::vector<HashTableSlot<KeyType, DataType>*>& bucket : buckets) {
		if (!bucket.empty()) {
			std::size_t secondaryTableSize = bucket.size() * bucket.size();
			primaryTable[i] = new HashTable<KeyType, DataType>(secondaryTableSize);
			bool isInsertSuccessfully = primaryTable[i]->insert(bucket);

			// Repeats the insertion until no successful insertion (without collision) in the secondary hash table.
			while (!isInsertSuccessfully) {
				delete primaryTable[i];
				primaryTable[i] = new HashTable<KeyType, DataType>(secondaryTableSize);
				isInsertSuccessfully = primaryTable[i]->insert(bucket);
			}
		}
		i++;
	}
}

template<typename KeyType, typename DataType>
inline PerfectHashTable<KeyType, DataType>::PerfectHashTable(const std::vector<HashTableSlot<KeyType, DataType>*>& slots) : 
	size(slots.size()),
	hashFunction(slots.size())
{
	if (this->size == 0) {
		throw std::invalid_argument("Unable to create an empty hash table.");
	}

	primaryTable = new HashTable<KeyType, DataType>* [size]();
	insert(slots);
}

// TODO: Use smart pointers.
template<typename KeyType, typename DataType>
inline PerfectHashTable<KeyType, DataType>::~PerfectHashTable()
{
	for (std::size_t i = 0; i < size; i++) {
		delete primaryTable[i];
	}
	delete[] primaryTable;
}

// Returns the pointer to data if the search is successful otherwise returns nullptr.
template<typename KeyType, typename DataType>
inline DataType* PerfectHashTable<KeyType, DataType>::search(KeyType key)
{
	std::size_t index = hashFunction.getHashValue(key);
	if (primaryTable[index]) {
		return primaryTable[index]->search(key);
	}
	return nullptr;
}

template<typename KeyType, typename DataType>
inline void PerfectHashTable<KeyType, DataType>::printKeys()
{
	for (std::size_t i = 0; i < size; i++) {
		std::cout << i << ": ";
		if (primaryTable[i]) {
			primaryTable[i]->printKeys();
		}
		else {
			std::cout << "_" << std::endl;
		}
	}
}