#pragma once

#include "HashFunction.h"
#include <cstddef>

template <typename T>
class HashTable
{
private:
	T** table;
	std::size_t size;

	HashFunction hashFunction;

public:
	HashTable(std::size_t size);
	~HashTable();
};

template<typename T>
inline HashTable<T>::HashTable(std::size_t size) : table(new T*[size]()), size(size), hashFunction(size)
{
	
}

template<typename T>
inline HashTable<T>::~HashTable()
{
	for (std::size_t i = 0; i < size; i++) {
		delete table[i];
	}
	delete[] table;
}