#pragma once

#include <string>

class HashFunction
{
public:
	static const unsigned p = 4294967291; // 2^32 - 5 (prime)

	unsigned a;
	unsigned b;
	unsigned m;

public:
	HashFunction(unsigned m);

	unsigned getHashValue(std::string key);
};