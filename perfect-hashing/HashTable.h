#pragma once

#include "HashFunction.h"
#include <cstddef>

template <typename T>
class HashTable
{
private:
	T** table;
	size_t size;

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
	delete[] table;
}