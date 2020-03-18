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

template <typename T>
class SplayTree
{
private:
	TreeNode<T>* root;

	void rotateLeft(TreeNode<T>* x);
	void rotateRight(TreeNode<T>* y);

public:
	SplayTree();

};

template<typename T>
inline TreeNode<T>::TreeNode(T key) : key(key), parent(nullptr), left(nullptr), right(nullptr)
{
}

template<typename T>
inline void SplayTree<T>::rotateLeft(TreeNode<T>* x)
{
	if (!x || !x->right) {
		return;
	}

	TreeNode<T>* y = x->right;
	x->right = y->left;
	if (y->left) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (!x->parent) {
		this->root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

template<typename T>
inline void SplayTree<T>::rotateRight(TreeNode<T>* y)
{
	if (!y || !y->left) {
		return;
	}

	TreeNode<T>* x = y->left;
	y->left = x->right;
	if (x->right) {
		x->right->parent = y;
	}
	x->parent = y->parent;
	if (!y->parent) {
		this->root = x;
	}
	else if (y == y->parent->right) {
		y->parent->right = x;
	}
	else {
		y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
}

template<typename T>
inline SplayTree<T>::SplayTree() : root(nullptr)
{
}
