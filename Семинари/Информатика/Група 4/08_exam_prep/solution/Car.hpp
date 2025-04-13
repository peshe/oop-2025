#pragma once

#include "Date.hpp"
#include <istream>
#include <ostream>
#include <iostream>

class Car
{
public:
	enum class BOOT_TYPE
	{
		UNKNOWN = -1,
		SEDAN,
		KOMBI,
		HATCHBACK
	};

	Car() = default;
	
	// For testing
	Car(const char* brand, const Date& date, BOOT_TYPE bootType, double enginePower, unsigned seats);

	Car(std::istream& is);

	Car(const Car& other);

	Car& operator=(const Car& other);

	~Car();
	
	void print(std::ostream& os = std::cout) const;

	const char* getBrand() const;
	Date getManufactureDate() const;
	BOOT_TYPE getBootType() const;
	double getEnginePower() const;
	unsigned getSeatCapacity() const;

	void setBrand(const char* brand);
	void setManufactureDate(const Date& date);
	void setEnginePower(double enginePower);
	void setSeatCapacity(unsigned int seatCapacity);

	static double getTotalEnginePower();


private:
	void free();
	void copyCar(const Car& other);

	static double totalEnginePower;

	char* brand;
	Date manufactureDate;
	const BOOT_TYPE bootType = BOOT_TYPE::UNKNOWN;
	double enginePower;
	unsigned int seatCapacity;
};

