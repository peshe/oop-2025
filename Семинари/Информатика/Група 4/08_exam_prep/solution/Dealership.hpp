#pragma once

#include "Car.hpp"
#include <iostream>

class Dealership
{
public:
	Dealership(std::size_t capacity = 0);

	// TODO:
	Dealership(const Dealership& other) = delete;
	Dealership& operator=(const Dealership& other) = delete;

	~Dealership();

	std::size_t add(const Car& car, double price);
	Car sell(std::size_t index);

	void print(std::ostream& os = std::cout) const;
	void printStats(std::ostream& os = std::cout) const;
	void printCriteria(bool (*predicate)(const Car& car), std::ostream& os = std::cout) const;

private:
	struct DealershipPair
	{
		Car car;
		double price;
	};

	DealershipPair** data;
	std::size_t size;
	std::size_t capacity;

	unsigned int soldCarCount;
	double totalRevenue;

	void free();
};

