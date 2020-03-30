#pragma once

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <iostream>

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
	std::size_t** roots;

	void calculate(double* probabilities);
	void build(TreeNode<T>*& tree, std::size_t i, std::size_t j);

	void deleteTreeNode(TreeNode<T>* node);
	
	void printDotVertices(TreeNode<T>* tree, std::ostream& out);
	void printDotEdges(TreeNode<T>* tree, std::ostream& out);

public:
	OptimalBinarySearchTree(T* keys, double* probabilities, std::size_t size);
	~OptimalBinarySearchTree();

	double getExpectedSearchCost();

	// Prints the tree in the DOT language.
	void printDotLanguage(std::ostream& out = std::cout);
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
		roots[i][i] = i;
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
					roots[i][j] = r;
				}
			}
		}
	}
}

template<typename T>
inline void OptimalBinarySearchTree<T>::build(TreeNode<T>*& tree, std::size_t i, std::size_t j)
{
	if (i > j) {
		throw std::invalid_argument("Invalid range. Cannot build a tree on this range.");
	}
	std::size_t r = roots[i][j];
	tree = new TreeNode<T>(keys[r]);
	if (r > i) {
		build(tree->left, i, r - 1);
	}
	if (r < j) {
		build(tree->right, r + 1, j);
	}
}

template<typename T>
inline void OptimalBinarySearchTree<T>::deleteTreeNode(TreeNode<T>* node)
{
	if (!node) {
		return;
	}
	deleteTreeNode(node->left);
	deleteTreeNode(node->right);
	delete node;
}

template<typename T>
inline void OptimalBinarySearchTree<T>::printDotVertices(TreeNode<T>* tree, std::ostream& out)
{
	if (!tree) {
		return;
	}
	out << tree->id << " [label=" << tree->key << "]" << std::endl;
	printDotVertices(tree->left, out);
	if (tree->left || tree->right) {
		out << "invis" << tree->id << " [label=\"\", width=.8, style=invis]" << std::endl;
	}
	printDotVertices(tree->right, out);
}

template<typename T>
inline void OptimalBinarySearchTree<T>::printDotEdges(TreeNode<T>* tree, std::ostream& out)
{
	if (!tree) {
		return;
	}
	if (tree->left) {
		out << tree->id << " -> ";
		printDotEdges(tree->left, out);
	}
	if (tree->right) {
		out << tree->id << " -> ";
		printDotEdges(tree->right, out);
	}
	if (!tree->right && !tree->left) {
		out << tree->id << std::endl;
	}
	else {
		out << tree->id << " -> " << "invis" << tree->id << " [style=invis]" << std::endl;
	}
}

template<typename T>
inline OptimalBinarySearchTree<T>::OptimalBinarySearchTree(T* keys, double* probabilities, std::size_t size) 
	: roots(nullptr), keys(keys), size(size)
{
	if (size == 0) {
		throw std::invalid_argument("The size cannot be 0.");
	}
	e = new double* [size];
	w = new double* [size];
	roots = new std::size_t* [size];
	for (std::size_t i = 0; i < size; i++) {
		e[i] = new double[size] {};
		w[i] = new double[size] {};
		roots[i] = new std::size_t[size] {};
	}
	calculate(probabilities);
	build(this->root, 0, size - 1);
}

template<typename T>
inline OptimalBinarySearchTree<T>::~OptimalBinarySearchTree()
{
	for (std::size_t i = 0; i < size; i++) {
		delete[] e[i];
		delete[] w[i];
		delete[] roots[i];
	}
	delete[] e;
	delete[] w;
	delete[] roots;
	deleteTreeNode(this->root);
}

template<typename T>
inline double OptimalBinarySearchTree<T>::getExpectedSearchCost()
{
	return e[0][size - 1];
}

template<typename T>
inline void OptimalBinarySearchTree<T>::printDotLanguage(std::ostream& out)
{
	if (!this->root) {
		return;
	}
	out << "digraph G {" << std::endl;
	out << "node[style=filled, fillcolor=lightblue, fontname=Helvetica, fontsize=20]" << std::endl;
	printDotVertices(this->root, out);
	printDotEdges(this->root, out);
	out << "}" << std::endl;
}
