#include <random>
#include "HashFunction.h"

HashFunction::HashFunction(unsigned m) : m(m)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<unsigned> dis1(1, p - 1);
	std::uniform_int_distribution<unsigned> dis2(0, p - 1);

	a = dis1(generator);
	b = dis2(generator);
}

// TODO: Add hash function from universal class of hash functions here.
unsigned HashFunction::getHashValue(std::string key)
{
	return 0;
}

unsigned HashFunction::getHashValue(unsigned key)
{
	return ((a * key + b) % p) % m;
}
