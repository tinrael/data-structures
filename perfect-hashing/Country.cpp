#include "Country.h"

Country::Country() : population(0), hdi(0)
{
}

Country::Country(std::string name, std::string capital, unsigned population, double hdi) : 
	name(name), 
	capital(capital), 
	population(population), 
	hdi(hdi)
{
}

Country& Country::operator=(const Country& country)
{
	if (this != &country) {
		name = country.name;
		capital = country.capital;
		population = country.population;
		hdi = country.hdi;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Country& country)
{
	out << "Country: " << country.name << std::endl;
	out << "Capital: " << country.capital << std::endl;
	out << "Population: " << country.population << std::endl;
	out << "HDI: " << country.hdi << std::endl;

	return out;
}