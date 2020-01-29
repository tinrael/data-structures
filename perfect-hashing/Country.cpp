#include "Country.h"

Country::Country(std::string name, std::string capital, int population, double hdi) : name(name), capital(capital), population(population), hdi(hdi)
{
}

std::ostream& operator<<(std::ostream& out, const Country& country)
{
	out << "Country: " << country.name << std::endl;
	out << "Capital: " << country.capital << std::endl;
	out << "Population: " << country.population << std::endl;
	out << "HDI: " << country.hdi << std::endl;

	return out;
}