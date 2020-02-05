#include <random>
#include "HashFunction.h"

HashFunction::HashFunction(std::size_t m) : m(m)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<unsigned> disA(1, p - 1);
	std::uniform_int_distribution<unsigned> disB(0, p - 1);

	a = disA(generator);
	b = disB(generator);
}

// TODO: Add hash function from universal class of hash functions here.
std::size_t HashFunction::getHashValue(std::string key)
{
	return 0;
}

std::size_t HashFunction::getHashValue(unsigned key)
{
	return ((a * key + b) % p) % m;
}
