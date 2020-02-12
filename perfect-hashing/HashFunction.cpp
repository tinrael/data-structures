#include "HashFunction.h"
#include <random>
#include <stdexcept>

HashFunction::HashFunction(std::size_t m)
{
	if (m == 0) {
		throw std::invalid_argument("The m value cannot be zero.");
	}
	
	this->m = m;

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<unsigned> disA(1, p - 1);
	std::uniform_int_distribution<unsigned> disB(0, p - 1);

	a = disA(generator);
	b = disB(generator);
}

std::size_t HashFunction::getHashValue(std::string key)
{
	unsigned result = 0;
	for (const char &symbol : key) {
		result = (a * symbol + result + b) % p;
	}
	return result % m;
}

std::size_t HashFunction::getHashValue(unsigned key)
{
	return ((a * key + b) % p) % m;
}