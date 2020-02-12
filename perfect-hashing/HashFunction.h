#pragma once

#include <string>
#include <cstddef>

class HashFunction
{
public:
	static const unsigned p = 524309; // prime number

	unsigned a; // the random in [1, p - 1]
	unsigned b; // the random in [0, p - 1]
	std::size_t m;

public:
	HashFunction(std::size_t m);

	std::size_t getHashValue(std::string key);
	std::size_t getHashValue(unsigned key);
};