#include "InMemoryFurnitureCatalog.hpp"

#include <stdexcept>

InMemoryFurnitureCatalog::InMemoryFurnitureCatalog(std::size_t initialCapacity): size(0), capacity(initialCapacity),
    data(nullptr) {
    this->data = new Furniture *[initialCapacity];
    for (std::size_t i = 0; i < initialCapacity; ++i) {
        this->data[i] = nullptr;
    }
}

InMemoryFurnitureCatalog::~InMemoryFurnitureCatalog() {
    for (std::size_t i = 0; i < size; ++i) {
        delete this->data[i];
    }
    delete[] this->data;
}

void InMemoryFurnitureCatalog::resizeData() {
    Furniture **newData = new Furniture *[this->capacity * 2];
    for (std::size_t i = 0; i < this->capacity; ++i) {
        newData[i] = this->data[i];
    }
    delete[] this->data;
    this->data = newData;
    this->capacity *= 2;
}

void InMemoryFurnitureCatalog::create(const Furniture &furn) {
    if (this->size >= this->capacity) {
        this->resizeData();
    }
    this->data[this->size] = furn.clone();
    this->size++;
}

const Furniture &InMemoryFurnitureCatalog::read(const char *model) const {
    for (std::size_t i = 0; i < this->size; ++i) {
        if (this->data[i] != nullptr && std::strcmp(this->data[i]->getModelName(), model) == 0) {
            return *this->data[i];
        }
    }
    throw std::invalid_argument("InMemoryFurnitureCatalog::read() model doesn't exist");
}

void InMemoryFurnitureCatalog::update(const char *model, const Furniture &newFurn) {
    for (std::size_t i = 0; i < this->size; ++i) {
        if (this->data[i] != nullptr && std::strcmp(this->data[i]->getModelName(), model) == 0) {
            delete this->data[i];
            this->data[i] = newFurn.clone();
            return;
        }
    }
    throw std::invalid_argument("InMemoryFurnitureCatalog::read() model doesn't exist");
}

void InMemoryFurnitureCatalog::remove(const char *model) {
    for (std::size_t i = 0; i < this->size; ++i) {
        if (this->data[i] != nullptr && std::strcmp(this->data[i]->getModelName(), model) == 0) {
            delete this->data[i];
            // Shift records
            for (std::size_t j = i; j < this->size - 1; ++j) {
                this->data[j] = this->data[j + 1];
            }
            this->size--;
            return;
        }
    }
    throw std::invalid_argument("InMemoryFurnitureCatalog::read() model doesn't exist");
}
