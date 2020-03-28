#pragma once

#include <cstddef>
#include <limits>

template <typename T>
class OptimalBinarySearchTree
{
private:
	double** e;
	double** w;
	std::size_t size;

	void calculate(T* keys, double* probabilities);

public:
	OptimalBinarySearchTree(T* keys, double* probabilities, std::size_t size);
	~OptimalBinarySearchTree();

};

template<typename T>
inline void OptimalBinarySearchTree<T>::calculate(T* keys, double* probabilities)
{
	for (std::size_t i = 0; i < size; i++) {
		e[i][i] = probabilities[i];
		w[i][i] = probabilities[i];
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
				}
			}
		}
	}
}

template<typename T>
inline OptimalBinarySearchTree<T>::OptimalBinarySearchTree(T* keys, double* probabilities, std::size_t size) 
	: size(size)
{
	e = new double* [size];
	w = new double* [size];
	for (std::size_t i = 0; i < size; i++) {
		e[i] = new double[size] {};
		w[i] = new double[size] {};
	}
	calculate(keys, probabilities);
}

template<typename T>
inline OptimalBinarySearchTree<T>::~OptimalBinarySearchTree()
{
	for (std::size_t i = 0; i < size; i++) {
		delete[] e[i];
		delete[] w[i];
	}
	delete[] e;
	delete[] w;
}
