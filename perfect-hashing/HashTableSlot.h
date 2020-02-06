#pragma once

template<typename KeyType, typename DataType>
class HashTableSlot
{
private:
	KeyType key;
	DataType *data;

public:
	HashTableSlot(KeyType key, DataType *data);
	~HashTableSlot();

	KeyType getKey();
	DataType* getData();
};

template<typename KeyType, typename DataType>
inline HashTableSlot<KeyType, DataType>::HashTableSlot(KeyType key, DataType *data) : key(key), data(data)
{
}

// TODO: Use smart pointers. Are you sure to delete data?
template<typename KeyType, typename DataType>
inline HashTableSlot<KeyType, DataType>::~HashTableSlot()
{
	delete data;
}

template<typename KeyType, typename DataType>
inline KeyType HashTableSlot<KeyType, DataType>::getKey()
{
	return key;
}

template<typename KeyType, typename DataType>
inline DataType* HashTableSlot<KeyType, DataType>::getData()
{
	return data;
}