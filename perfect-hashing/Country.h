#pragma once

#include <iostream>
#include <string>

class Country
{
private:
	std::string name;
	std::string capital;
	int population;
	double hdi; // The Human Development Index

public:
	Country(std::string name, std::string capital, int population, double hdi);

	friend std::ostream& operator<< (std::ostream& out, const Country& country);
};