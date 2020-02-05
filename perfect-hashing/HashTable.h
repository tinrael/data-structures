#pragma once

#include "HashTableSlot.h"
#include "HashFunction.h"
#include <cstddef>
#include <stdexcept>

template<typename T, typename U>
class HashTable
{
private:
	HashTableSlot<T, U> **table;
	std::size_t size;

	HashFunction hashFunction;

public:
	HashTable(std::size_t size);
	~HashTable();

	bool insert(HashTableSlot<T, U>* slot);
};

template<typename T, typename U>
inline HashTable<T, U>::HashTable(std::size_t size) : table(new HashTableSlot<T, U>*[size]()), size(size), hashFunction(size)
{
	
}

template<typename T, typename U>
inline HashTable<T, U>::~HashTable()
{
	for (std::size_t i = 0; i < size; i++) {
		delete table[i];
	}
	delete[] table;
}

template<typename T, typename U>
inline bool HashTable<T, U>::insert(HashTableSlot<T, U> *slot)
{
	if (!data) {
		throw std::invalid_argument("nullptr data argument");
	}
	std::size_t index = hashFunction.getHashValue(slot->getKey());
	if (!table[index]) {
		table[index] = slot;
		return true;
	}
	return false;
}