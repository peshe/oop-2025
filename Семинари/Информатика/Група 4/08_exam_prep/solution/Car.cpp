#include "Car.hpp"
#include <stdexcept>
#include <cstring>

const char PRINT_DELIMITER = ' ';
double Car::totalEnginePower = 0;

Car::BOOT_TYPE readBootTypeFromStream(std::istream& is) {
	if (!is) {
		throw std::invalid_argument("Invalid stream");
	}

	const std::size_t BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE];
	is >> buffer;

	if (std::strcmp(buffer, "Sedan") == 0) {
		return Car::BOOT_TYPE::SEDAN;
	}

	if (std::strcmp(buffer, "Kombi") == 0) {
		return Car::BOOT_TYPE::KOMBI;
	}

	if (std::strcmp(buffer, "Hatchback") == 0) {
		return Car::BOOT_TYPE::HATCHBACK;
	}
	
	return Car::BOOT_TYPE::UNKNOWN;
}

Date readDateFromStream(std::istream& is) {
	if (!is) {
		throw std::invalid_argument("Invalid stream");
	}
	const std::size_t BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE];
	is >> buffer;

	return Date(buffer);
}

char* copyString(const char* str) {
	if (!str) {
		throw std::invalid_argument("Invalid string");
	}
	char* copy = new char[std::strlen(str) + 1];
	std::strcpy(copy, str);
	return copy;
}


Car::Car(std::istream& is)
	: bootType(readBootTypeFromStream(is)), brand(nullptr), manufactureDate(), enginePower(),
	seatCapacity()
{
	if (!is) {
		throw std::invalid_argument("Invalid stream");
	}

	this->setManufactureDate(readDateFromStream(is));

	const std::size_t BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE];
	is >> buffer;

	this->setBrand(buffer);

	double enginePower;
	is >> enginePower;
	this->setEnginePower(enginePower);

	unsigned seats;
	is >> seats;
	this->setSeatCapacity(seats);

	if (!is) {
		this->free();
		throw std::invalid_argument("Error reading from stream");
	}

	Car::totalEnginePower += this->getEnginePower();
}

Car::Car(const Car& other)
{
	this->copyCar(other);
	Car::totalEnginePower += this->getEnginePower();
}

Car& Car::operator=(const Car& other)
{
	if (this != &other) {
		this->free();
		double oldEnginePower = this->getEnginePower();
		this->copyCar(other);
		Car::totalEnginePower -= oldEnginePower;
		Car::totalEnginePower += this->getEnginePower();
	}

	return *this;
}

Car::~Car()
{
	this->free();
}

void Car::print(std::ostream& os) const
{
	switch (this->bootType)
	{
	case BOOT_TYPE::SEDAN: os << "Sedan"; break;
	case BOOT_TYPE::KOMBI: os << "Kombi"; break;
	case BOOT_TYPE::HATCHBACK: os << "Hatchback"; break;
	default:
		os << "UNKNOWN";
		break;
	}
	os << PRINT_DELIMITER;

	this->manufactureDate.print(os);
	os << PRINT_DELIMITER;

	os << this->getBrand() << PRINT_DELIMITER;
	os << this->getEnginePower() << PRINT_DELIMITER;
	os << this->getSeatCapacity() << PRINT_DELIMITER;

	os << std::endl;
}

const char* Car::getBrand() const
{
	return this->brand;
}

Date Car::getManufactureDate() const
{
	return this->manufactureDate;
}

Car::BOOT_TYPE Car::getBootType() const
{
	return this->bootType;
}

double Car::getEnginePower() const
{
	return this->enginePower;
}

unsigned Car::getSeatCapacity() const
{
	return this->seatCapacity;
}

void Car::setBrand(const char* brand)
{
	char* newBrand = copyString(brand);
	delete[] this->brand;
	this->brand = newBrand;
}

void Car::setManufactureDate(const Date& date)
{
	this->manufactureDate = date;
}

void Car::setEnginePower(double enginePower)
{
	this->enginePower = enginePower;
}

void Car::setSeatCapacity(unsigned int seatCapacity)
{
	this->seatCapacity = seatCapacity;
}

double Car::getTotalEnginePower()
{
	return Car::totalEnginePower;
}

void Car::free()
{
	delete[] this->brand;
}

void Car::copyCar(const Car& other)
{
	this->brand = copyString(other.brand);
	this->enginePower = other.enginePower;
	this->seatCapacity = other.seatCapacity;
	this->manufactureDate = other.manufactureDate;
}
