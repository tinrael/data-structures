#pragma once

#include "HashTableSlot.h"
#include "HashFunction.h"
#include <cstddef>
#include <stdexcept>
#include <vector>

template<typename KeyType, typename DataType>
class HashTable
{
private:
	HashTableSlot<KeyType, DataType>** table;
	std::size_t size;

	HashFunction hashFunction;

public:
	HashTable(std::size_t size);
	~HashTable();

	bool insert(const std::vector<HashTableSlot<KeyType, DataType>*>& slots);
	bool insert(HashTableSlot<KeyType, DataType>* slot);
	DataType* search(KeyType key);
};

template<typename KeyType, typename DataType>
inline HashTable<KeyType, DataType>::HashTable(std::size_t size) : size(size), hashFunction(size)
{
	if (this->size == 0) {
		throw std::invalid_argument("The size of the hash table cannot be zero.");
	}
	table = new HashTableSlot<KeyType, DataType>*[size]();
}

// TODO: Use smart pointers. Are you sure to delete hash-table slots?
template<typename KeyType, typename DataType>
inline HashTable<KeyType, DataType>::~HashTable()
{
	for (std::size_t i = 0; i < size; i++) {
		delete table[i];
	}
	delete[] table;
}

/* Returns true if all the slots insert without collision.
Otherwise, only the slots which collide do not insert, and the false value returns.
 */
template<typename KeyType, typename DataType>
inline bool HashTable<KeyType, DataType>::insert(const std::vector<HashTableSlot<KeyType, DataType>*>& slots)
{
	if (slots.empty()) {
		throw std::invalid_argument("No slots to insert in the hash table.");
	}
	bool isInsertSuccessfully = true;
	for (HashTableSlot<KeyType, DataType>* slot : slots) {
		if (!insert(slot)) {
			isInsertSuccessfully = false;
		}
	}
	return isInsertSuccessfully;
}

/* Returns true if the slot inserts without collision.
Otherwise, the slot does not insert, and the false value returns.
 */
template<typename KeyType, typename DataType>
inline bool HashTable<KeyType, DataType>::insert(HashTableSlot<KeyType, DataType>* slot)
{
	if (!slot || !slot->getData()) {
		throw std::invalid_argument("The slot argument is incorrect.");
	}
	std::size_t index = hashFunction.getHashValue(slot->getKey());
	if (!table[index]) {
		table[index] = slot;
		return true;
	}
	return false;
}

// Returns the pointer to data if the search is successful otherwise returns nullptr.
template<typename KeyType, typename DataType>
inline DataType* HashTable<KeyType, DataType>::search(KeyType key)
{
	std::size_t index = hashFunction.getHashValue(key);
	if (table[index] && (table[index]->getKey() == key)) {
		return table[index]->getData();
	}
	return nullptr;
}