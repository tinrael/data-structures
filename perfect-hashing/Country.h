#pragma once

#include <iostream>
#include <string>
#include <fstream>

class Country
{
private:
	std::string name;
	std::string capital;
	unsigned population;
	double hdi; // The Human Development Index

public:
	Country();
	Country(std::string name, std::string capital, unsigned population, double hdi);

	bool save(std::ofstream& filename);
	bool load(std::ifstream& filename);

	Country& operator= (const Country& country);
	friend std::ostream& operator<< (std::ostream& out, const Country& country);

	std::string getName();
};