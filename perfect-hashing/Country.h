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
	Country();
	Country(std::string name, std::string capital, int population, double hdi);

	Country& operator= (const Country& country);

	friend std::ostream& operator<< (std::ostream& out, const Country& country);
};