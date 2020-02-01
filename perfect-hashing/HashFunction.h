#pragma once

#include <string>

class HashFunction
{
public:
	static const unsigned p = 262139; // prime number

	unsigned a; // the random in [1, p - 1]
	unsigned b; // the random in [0, p - 1]
	unsigned m;

public:
	HashFunction(unsigned m);

	unsigned getHashValue(std::string key);
	unsigned getHashValue(unsigned key);
};