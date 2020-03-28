#pragma once

#include <cstddef>
#include <limits>

template <typename T>
class TreeNode {
public:
	static std::size_t idGenerator;
	std::size_t id;

	T key;

	TreeNode<T>* parent;
	TreeNode<T>* left;
	TreeNode<T>* right;

	TreeNode(T key);
};

template <typename T>
class OptimalBinarySearchTree
{
private:
	TreeNode<T>* root;

	T* keys;
	std::size_t size;
	
	double** e;
	double** w;
	std::size_t** root;

	void calculate(double* probabilities);

public:
	OptimalBinarySearchTree(T* keys, double* probabilities, std::size_t size);
	~OptimalBinarySearchTree();

};

template<typename T>
std::size_t TreeNode<T>::idGenerator = 0;

template<typename T>
inline TreeNode<T>::TreeNode(T key) : id(idGenerator), key(key), parent(nullptr), left(nullptr), right(nullptr)
{
	idGenerator++;
}

template<typename T>
inline void OptimalBinarySearchTree<T>::calculate(double* probabilities)
{
	for (std::size_t i = 0; i < size; i++) {
		e[i][i] = probabilities[i];
		w[i][i] = probabilities[i];
		root[i][i] = i;
	}
	for (std::size_t l = 1; l <= size - 1; l++) {
		for (std::size_t i = 0; i < size - l; i++) {
			std::size_t j = i + l;
			e[i][j] = std::numeric_limits<double>::max();
			w[i][j] = w[i][j - 1] + probabilities[j];
			for (std::size_t r = i; r <= j; r++) {
				double t = ((r > i) ? e[i][r - 1] : 0) + ((r < j) ? e[r + 1][j] : 0) + w[i][j];		
				if (t < e[i][j]) {
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}
}

template<typename T>
inline OptimalBinarySearchTree<T>::OptimalBinarySearchTree(T* keys, double* probabilities, std::size_t size) 
	: root(nullptr), keys(keys), size(size)
{
	e = new double* [size];
	w = new double* [size];
	root = new std::size_t* [size];
	for (std::size_t i = 0; i < size; i++) {
		e[i] = new double[size] {};
		w[i] = new double[size] {};
		root[i] = new std::size_t[size] {};
	}
	calculate(probabilities);
}

template<typename T>
inline OptimalBinarySearchTree<T>::~OptimalBinarySearchTree()
{
	for (std::size_t i = 0; i < size; i++) {
		delete[] e[i];
		delete[] w[i];
		delete[] root[i];
	}
	delete[] e;
	delete[] w;
	delete[] root;
}
