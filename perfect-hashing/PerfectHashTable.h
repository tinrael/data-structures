#pragma once

#include "HashTable.h"
#include "HashTableSlot.h"

template<typename KeyType, typename DataType>
class PerfectHashTable
{
private:
	HashTable<KeyType, HashTable<KeyType, DataType>> table;

public:
	PerfectHashTable(const std::vector<HashTableSlot<KeyType, DataType>*>& slots);
	DataType* search(KeyType key);
};

template<typename KeyType, typename DataType>
inline PerfectHashTable<KeyType, DataType>::PerfectHashTable(const std::vector<HashTableSlot<KeyType, DataType>*>& slots)
{
}

template<typename KeyType, typename DataType>
inline DataType* PerfectHashTable<KeyType, DataType>::search(KeyType key)
{
	return nullptr;
}