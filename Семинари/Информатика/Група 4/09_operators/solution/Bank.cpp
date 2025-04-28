#include "Bank.hpp"

#include <cstring>
#include <cassert>
#include <new>


Bank::Bank(const char *name, const ConversionRate rates[CONVERSION_RATES_SIZE]) {
    this->allocateClientsMemory(INITIAL_CLIENTS_CAPACITY);

    this->setName(name);
    this->setConversionRates(rates);
}

Bank::Bank(const Bank &other) {
    this->copyDataFrom(other);
}

Bank &Bank::operator=(const Bank &other) {
    if (this != &other) {
        this->deleteData();
        this->copyDataFrom(other);
    }

    return *this;
}

Bank::~Bank() {
    this->deleteData();
}

void Bank::addClient(const Client &client) {
    if (this->clientsSize >= this->clientsCapacity) {
        this->allocateClientsMemory(this->clientsCapacity * CLIENTS_CAPACITY_MULTIPLIER);
    }

    this->clients[this->clientsSize++] = new Client(client);
}

bool Bank::removeClient(const char *identificationNumber) {
    int clientIndex{this->getClientIndex(identificationNumber)};

    if (clientIndex == -1) {
        return false;
    }

    delete this->clients[clientIndex];
    this->clients[clientIndex] = this->clients[this->clientsSize - 1];
    this->clients[--this->clientsSize] = nullptr;

    return true;
}

int Bank::getClientIndex(const char *identificationNumber) const {
    for (std::size_t index{0}; index < this->clientsSize; ++index) {
        if (strcmp(this->clients[index]->getIdentificationNumber(), identificationNumber) == 0) {
            return index;
        }
    }

    return -1;
}

bool Bank::deposit(const char *identificationNumber, const Money &toDeposit) {
    int clientIndex{this->getClientIndex(identificationNumber)};

    if (clientIndex == -1) {
        return false;
    }

    return this->clients[clientIndex]->deposit(toDeposit);
}

bool Bank::withdraw(const char *identificationNumber, const Money &toWithdraw) {
    int clientIndex{this->getClientIndex(identificationNumber)};

    if (clientIndex == -1) {
        return false;
    }

    return this->clients[clientIndex]->withdraw(toWithdraw);
}

bool Bank::transfer(const char *sourceClientIdentificationNumber, const char *destinationClientIdentifinationNumber,
                    Money moneyToTransfer) {
    int sourceIndex{this->getClientIndex(sourceClientIdentificationNumber)};

    if (sourceIndex == -1) {
        return false;
    }

    int destinationIndex{this->getClientIndex(destinationClientIdentifinationNumber)};

    if (destinationIndex == -1) {
        return false;
    }

    Client *source{this->clients[sourceIndex]};
    Client *destination{this->clients[destinationIndex]};

    if (moneyToTransfer.getCurrency() != source->getMoney().getCurrency()) {
        const ConversionRate *conversionRate = this->findConversionRate(moneyToTransfer.getCurrency(),
                                                                        source->getMoney().getCurrency());

        if (conversionRate == nullptr) {
            return false;
        }

        moneyToTransfer.hardConvert(*conversionRate);
    }

    if (source->getMoney() < moneyToTransfer) {
        return false;
    }

    source->withdraw(moneyToTransfer);

    if (moneyToTransfer.getCurrency() != destination->getMoney().getCurrency()) {
        const ConversionRate *conversionRate = this->findConversionRate(moneyToTransfer.getCurrency(),
                                                                        destination->getMoney().getCurrency());

        if (conversionRate == nullptr) {
            return false;
        }

        moneyToTransfer.hardConvert(*conversionRate);
    }

    destination->deposit(moneyToTransfer);

    return true;
}

bool Bank::convertClientMoney(const char *identificationNumber, Currency newCurrency) {
    int clientIndex{this->getClientIndex(identificationNumber)};

    if (clientIndex == -1) {
        return false;
    }

    const ConversionRate *conversionRate = this->findConversionRate(
        this->clients[clientIndex]->getMoney().getCurrency(), newCurrency);

    if (conversionRate == nullptr) {
        return false;
    }

    this->clients[clientIndex]->convert(*conversionRate);

    return true;
}

void Bank::allocateClientsMemory(std::size_t newCapacity) {
    if (newCapacity <= this->clientsCapacity) {
        newCapacity = this->clientsCapacity + 1;
    }

    Client **blockOfMem = new Client *[newCapacity];

    for (std::size_t index{0}; index < this->clientsSize; ++index) {
        blockOfMem[index] = new Client(*this->clients[index]);
    }

    this->deleteClients();

    this->clients = blockOfMem;
    this->clientsCapacity = newCapacity;
}

void Bank::copyDataFrom(const Bank &other) {
    this->setConversionRates(other.conversionRates);
    this->setName(other.name);

    this->clients = new(std::nothrow) Client *[other.clientsCapacity];

    for (std::size_t index{0}; index < other.clientsSize; ++index) {
        this->clients[index] = new(std::nothrow) Client(*other.clients[index]);
    }

    this->clientsCapacity = other.clientsCapacity;
    this->clientsSize = other.clientsSize;
}

void Bank::deleteClients() {
    for (std::size_t index{0}; index < clientsSize; ++index) {
        delete this->clients[index];
        this->clients[index] = nullptr;
    }

    delete[] this->clients;
    this->clients = nullptr;
}

void Bank::deleteData() {
    delete[] this->name;
    this->name = nullptr;

    this->deleteClients();
}

void Bank::setName(const char *name) {
    delete[] this->name;

    char *newName = new(std::nothrow) char[strlen(name) + 1];

    if (!name) {
        throw std::bad_alloc();
    }

    strcpy(newName, name);
    this->name = newName;
}

void Bank::setConversionRates(const ConversionRate conversionRates[CONVERSION_RATES_SIZE]) {
    for (std::size_t index{0}; index < CONVERSION_RATES_SIZE; ++index) {
        this->conversionRates[index] = conversionRates[index];
    }
}

const ConversionRate *Bank::findConversionRate(Currency oldCurrency, Currency newCurrency) const {
    for (std::size_t index{0}; index < CONVERSION_RATES_SIZE; ++index) {
        if (this->conversionRates[index].oldCurrency == oldCurrency && this->conversionRates[index].newCurrency ==
            newCurrency) {
            return this->conversionRates + index;
        }
    }

    return nullptr;
}
