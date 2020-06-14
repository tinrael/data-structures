#pragma once

#include "Node.h"

template <typename KeyType>
class BinomialHeap
{
private:
	Node<KeyType>* head;

public:
	BinomialHeap();

};

template<typename KeyType>
inline BinomialHeap<KeyType>::BinomialHeap() : head{ nullptr }
{
}
