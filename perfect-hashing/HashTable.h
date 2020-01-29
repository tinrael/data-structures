#pragma once

#include <cstddef>

template <typename T>
class HashTable
{
private:
	T* table;
	size_t size;

public:
	HashTable(std::size_t size);
	~HashTable();
};

template<typename T>
inline HashTable<T>::HashTable(std::size_t size) : size(size)
{
	table = new T[size];
}

template<typename T>
inline HashTable<T>::~HashTable()
{
	delete[] table;
}