#pragma once

template <typename T>
class TreeNode {
public:
	T key;

	TreeNode<T>* parent;
	TreeNode<T>* left;
	TreeNode<T>* right;

	TreeNode(T key);
};

class SplayTree
{
};

template<typename T>
inline TreeNode<T>::TreeNode(T key) : key(key), parent(nullptr), left(nullptr), right(nullptr)
{
}
