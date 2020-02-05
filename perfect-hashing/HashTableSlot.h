#pragma once

template<typename T, typename U>
class HashTableSlot
{
private:
	T key;
	U *data;

public:
	HashTableSlot(T key, U *data);
	~HashTableSlot();

	T getKey();
	U* getData();
};

template<typename T, typename U>
inline HashTableSlot<T, U>::HashTableSlot(T key, U *data) : key(key), data(data)
{
}

// TODO: Use smart pointers
template<typename T, typename U>
inline HashTableSlot<T, U>::~HashTableSlot()
{
	delete data;
}

template<typename T, typename U>
inline T HashTableSlot<T, U>::getKey()
{
	return key;
}

template<typename T, typename U>
inline U* HashTableSlot<T, U>::getData()
{
	return data;
}