#pragma once

template<typename KeyType, typename DataType>
class HashTableSlot
{
private:
	KeyType key;
	DataType* data;

public:
	HashTableSlot(KeyType key, DataType* data);

	KeyType getKey();
	DataType* getData();
};

// The slot does not take ownership of data.
template<typename KeyType, typename DataType>
inline HashTableSlot<KeyType, DataType>::HashTableSlot(KeyType key, DataType* data) : key(key), data(data)
{
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