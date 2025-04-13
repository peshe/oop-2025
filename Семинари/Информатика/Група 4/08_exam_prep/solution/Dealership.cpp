#include "Dealership.hpp"

Dealership::Dealership(std::size_t capacity)
	:capacity(capacity), size(0), data(nullptr), soldCarCount(0), totalRevenue(0)
{
	this->data = new DealershipPair * [capacity];
	for (size_t i = 0; i < this->capacity; i++)
	{
		this->data[i] = nullptr;
	}
}

Dealership::~Dealership()
{
	this->free();
}

std::size_t Dealership::add(const Car& car, double price)
{
	for (size_t i = 0; i < this->capacity; i++)
	{
		if (this->data[i] == nullptr) {
			this->data[i] = new DealershipPair{ car, price };
			this->size++;
			return i;
		}
	}

	throw std::out_of_range("Dealership is full");
}

Car Dealership::sell(std::size_t index)
{
	if (index >= this->capacity) {
		throw std::invalid_argument("invalid index");
	}
	if (this->data[index] == nullptr) {
		throw std::invalid_argument("invalid index");
	}

	this->soldCarCount++;
	this->totalRevenue += this->data[index]->price;

	this->size--;

	Car result(this->data[index]->car);

	delete this->data[index];
	this->data[index] = nullptr;

	return result;
}

void Dealership::free()
{
	for (size_t i = 0; i < this->capacity; i++)
	{
		delete this->data[i];
	}
	delete[] this->data;
}


void Dealership::print(std::ostream &os) const {
    for (std::size_t i = 0; i < this->capacity; i++) {
        if (this->data[i] == nullptr) {
            os << "<empty slot>";
            os << std::endl;
        } else {
            this->data[i]->car.print(os);
            os << "\tPrice: " << this->data[i]->price;
            os << std::endl;
        }
    }
}

void Dealership::printStats(std::ostream &os) const {
    os << "Sold cars count:\t" << this->soldCarCount << std::endl;
    os << "Revenue:\t" << this->totalRevenue << std::endl;
}

void Dealership::printCriteria(bool (*predicate)(const Car &), std::ostream &os) const {
    for (std::size_t i = 0; i < this->capacity; i++) {
        if (this->data[i] && predicate(this->data[i]->car)) {
            this->data[i]->car.print(os);
        }
    }
}
