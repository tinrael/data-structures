#pragma once

#include "HashTable.h"
#include "HashFunction.h"
#include "HashTableSlot.h"
#include <cstddef>
#include <vector>

template<typename KeyType, typename DataType>
class PerfectHashTable
{
private:
	HashTable<KeyType, DataType>** primaryTable;
	std::size_t size;

	HashFunction hashFunction;

public:
	PerfectHashTable(const std::vector<HashTableSlot<KeyType, DataType>*>& slots);
	~PerfectHashTable();

	DataType* search(KeyType key);
};

template<typename KeyType, typename DataType>
inline PerfectHashTable<KeyType, DataType>::PerfectHashTable(const std::vector<HashTableSlot<KeyType, DataType>*>& slots) : 
	primaryTable(new HashTable<KeyType, DataType>* [slots.size()]()),
	size(slots.size()),
	hashFunction(slots.size())
{
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

template<typename KeyType, typename DataType>
inline DataType* PerfectHashTable<KeyType, DataType>::search(KeyType key)
{
	return nullptr;
}