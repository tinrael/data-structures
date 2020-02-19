#include "Country.h"
#include <cstddef>

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

bool Country::save(std::ofstream& filename)
{
	std::size_t size = 0;

	size = name.size();
	filename.write((char*)& size, sizeof(size));
	filename.write(name.c_str(), size);

	size = capital.size();
	filename.write((char*)& size, sizeof(size));
	filename.write(capital.c_str(), size);

	filename.write((char*)& population, sizeof(population));
	filename.write((char*)& hdi, sizeof(hdi));

	if (filename.good()) {
		return true;
	}
	return false;
}

bool Country::load(std::ifstream& filename)
{
	std::size_t size = 0;
	char* buffer;

	filename.read((char*)& size, sizeof(size));
	buffer = new char[size + 1];
	filename.read(buffer, size);
	buffer[size] = '\0';
	name = buffer;
	delete[] buffer;
	buffer = nullptr;

	filename.read((char*)& size, sizeof(size));
	buffer = new char[size + 1];
	filename.read(buffer, size);
	buffer[size] = '\0';
	capital = buffer;
	delete[] buffer;
	buffer = nullptr;

	filename.read((char*)& population, sizeof(population));
	filename.read((char*)& hdi, sizeof(hdi));

	if (filename.good()) {
		return true;
	}
	return false;
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

std::string Country::getName()
{
	return name;
}