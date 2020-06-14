#pragma once

#include "Node.h"
#include <limits>
#include <stdexcept>
#include <utility>

template <typename KeyType>
class BinomialHeap
{
private:
	Node<KeyType>* head;

	void link(Node<KeyType>* y, Node<KeyType>* z);
	void combine(Node<KeyType>* h1, Node<KeyType>* h2);

	/*
	 * Merges two sorted in the ascending order singly linked lists together.
	 * Return the pointer to the new head node.
	*/
	Node<KeyType>* mergeLists(Node<KeyType>* x, Node<KeyType>* y);
	/*
	 * Reverses the singly linked list with the head node 'x'.
	 * Return the pointer to the new head node.
	*/
	Node<KeyType>* reverseList(Node<KeyType>* x);
	// Detaches the node 'x' from the singly linked list with the head node 'head'.
	void detachFromList(Node<KeyType>* head, Node<KeyType>* x);

public:
	BinomialHeap();

	void insert(KeyType key);
	void decreaseKey(Node<KeyType>* x, KeyType newKey);
	void erase(Node<KeyType>* x);
	Node<KeyType>* extractMin();
	Node<KeyType>* getMin();

};

template<typename KeyType>
inline void BinomialHeap<KeyType>::link(Node<KeyType>* y, Node<KeyType>* z)
{
	if (!y || !z) {
		throw std::invalid_argument("The null pointer is passed as the argument.");
	}

	y->parent = z;
	y->sibling = z->child;
	z->child = y;
	z->degree++;
}

template<typename KeyType>
inline void BinomialHeap<KeyType>::combine(Node<KeyType>* h1, Node<KeyType>* h2)
{
	this->head = mergeLists(h1, h2);
	if (!this->head) {
		return;
	}
	Node<KeyType>* prev = nullptr;
	Node<KeyType>* x = this->head;
	Node<KeyType>* next = x->sibling;
	while (next) {
		if ((x->degree != next->degree) || (next->sibling && (next->sibling->degree == x->degree))) {
			prev = x;
			x = next;
		}
		else {
			if (x->key <= next->key) {
				x->sibling = next->sibling;
				link(next, x);
			}
			else {
				if (!prev) {
					this->head = next;
				}
				else {
					prev->sibling = next;
				}
				link(x, next);
				x = next;
			}
		}

		next = x->sibling;
	}
}

template<typename KeyType>
inline Node<KeyType>* BinomialHeap<KeyType>::mergeLists(Node<KeyType>* x, Node<KeyType>* y)
{
	// TODO
	return nullptr;
}

template<typename KeyType>
inline Node<KeyType>* BinomialHeap<KeyType>::reverseList(Node<KeyType>* x)
{
	// TODO
	return nullptr;
}

template<typename KeyType>
inline void BinomialHeap<KeyType>::detachFromList(Node<KeyType>* head, Node<KeyType>* x)
{
	// TODO
}

template<typename KeyType>
inline BinomialHeap<KeyType>::BinomialHeap() : head{ nullptr }
{
}

template<typename KeyType>
inline void BinomialHeap<KeyType>::insert(KeyType key)
{
	Node<KeyType>* x = new Node<KeyType>(key);
	combine(this->head, x);
}

template<typename KeyType>
inline Node<KeyType>* BinomialHeap<KeyType>::extractMin()
{
	Node<KeyType>* x = getMin();
	if (!x) {
		return nullptr;
	}
	detachFromList(this->head, x);
	Node<KeyType>* y = reverseList(x->child);
	Node<KeyType>* cur = y;
	while (cur) {
		cur->parent = nullptr;
		cur = cur->sibling;
	}
	combine(this->head, y);
	return x;
}

template<typename KeyType>
inline void BinomialHeap<KeyType>::decreaseKey(Node<KeyType>* x, KeyType newKey)
{
	if (!x) {
		throw std::invalid_argument("The null pointer is passed as the argument 'x'.");
	}

	if (newKey > x->key) {
		throw std::invalid_argument("The new key value is higher than the old one.");
	}
	x->key = newKey;
	Node<KeyType>* y = x;
	Node<KeyType>* z = y->parent;
	while (z && (y->key < z->key)) {
		std::swap(y->key, z->key);
		y = z;
		z = y->parent;
	}
}

template<typename KeyType>
inline void BinomialHeap<KeyType>::erase(Node<KeyType>* x)
{
	if (!x) {
		throw std::invalid_argument("The null pointer is passed as the argument 'x'.");
	}

	decreaseKey(x, std::numeric_limits<KeyType>::lowest());
	delete extractMin();
}

template<typename KeyType>
inline Node<KeyType>* BinomialHeap<KeyType>::getMin()
{
	Node<KeyType>* y = nullptr;
	Node<KeyType>* x = this->head;
	KeyType min = std::numeric_limits<KeyType>::max();
	while (x) {
		if (x->key < min) {
			min = x->key;
			y = x;
		}
		x = x->sibling;
	}
	return y;
}
