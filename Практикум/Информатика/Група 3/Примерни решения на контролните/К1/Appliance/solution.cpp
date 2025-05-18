#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>

class String {
  // размер на буфера при въвеждане
  static const unsigned short MAX_INPUT_SIZE{100};

  char *data{nullptr};

  void destroy();
  void assign(const char *value);

public:
  String() = default;
  String(const char *value);
  String(std::istream &file, char delim = '\n');
  String(const String &other);
  String &operator=(const String &other);
  ~String();

  const char *getData() const { return data; }

  void print() const;
};

class Splitter;

class Appliance {
  static inline unsigned int numberOfAppliances;

  String description;
  String brand;
  float power;
  Splitter *splitter{nullptr};
  bool turnedOn{false};
  unsigned int serialNumber;

  void assign(const String &description, const String &brand, float power);

  void generateSerialNumber();

public:
  Appliance() = delete;
  Appliance(const String &description, const String &brand, float power);
  Appliance(std::istream &file);
  Appliance(const Appliance &other);
  Appliance &operator=(const Appliance &other);
  ~Appliance();

  const String &getDescription() const { return description; }
  const String &getBrand() const { return brand; }
  float getPower() const { return power; }
  bool isPluggedIn() const { return splitter != nullptr; }
  bool isTurnedOn() const { return turnedOn; }

  void setDescription(const String &description) {
    this->description = description;
  }
  void setBrand(const String &brand) { this->brand = brand; }
  bool setPower(float power);
  void plugIn(Splitter &splitter);
  void unplug();
  bool turnOn();
  void turnOff();

  void print() const;
};

class Splitter {
  const unsigned int numberOfSockets;
  float maxPower;
  unsigned int numberOfAppliances{0};
  Appliance **sockets;

  bool outOfOrder{false};

public:
  Splitter() = delete;
  Splitter(unsigned int numberOfSockets, float maxPower);
  Splitter(const Splitter &other);
  Splitter &operator=(const Splitter &other);
  ~Splitter();

  float getMaxPower() const { return maxPower; }
  float getCurrentPower() const;

  bool isOutOfOrder() const { return outOfOrder; }

  void handlePotentialOutOfOrderSituation();

  bool plugApplianceIn(Appliance &appliance);
  bool unplugAppliance(Appliance &appliance);

  void print() const;
};

class Appliances {
  const unsigned int numberOfAppliances{0};
  unsigned int currentNumberOfAppliances{0};
  Appliance **appliances;

public:
  Appliances() = delete;
  Appliances(unsigned int numberOfAppliances);
  Appliances(const Appliances &) = delete;
  Appliances &operator=(const Appliances &) = delete;
  ~Appliances();

  Appliance *getAppliance(unsigned int index);

  bool addAppliance(Appliance &appliance);
};

void assertIsNonEmpty(const char *value) {
  if (value == nullptr)
    throw "стойността на низа не може да е null";

  if (*value == '\0')
    throw "стойността на низа не може да е празна";
}

void String::destroy() {
  delete[] data;
  data = nullptr;
}

void String::assign(const char *value) {
  assertIsNonEmpty(value);

  destroy();

  size_t len{strlen(value) + 1};
  data = new char[len];
  strncpy(data, value, len);
}

String::String(const char *value) { assign(value); }

void handleInputErrors(const std::istream &input) {
  if (input.bad())
    throw "критична грешка при четене/въвеждане";

  if (!input)
    throw "опит за четене/въвеждане на невалидна или прекалено голяма стойност";
}

String::String(std::istream &file, char delim)
    : data{new char[MAX_INPUT_SIZE]} {
  file.getline(data, MAX_INPUT_SIZE, delim);
  handleInputErrors(file);
}

String::String(const String &other) : String{other.data} {}

String &String::operator=(const String &other) {
  if (&other != this) {
    assign(other.data);
  }
  return *this;
}

String::~String() { destroy(); }

void String::print() const {
  if (data != nullptr)
    std::cout << data;
}

void Appliance::assign(const String &description, const String &brand,
                       float power) {
  setDescription(description);
  setBrand(brand);
  setPower(power);
}

void Appliance::generateSerialNumber() { serialNumber = ++numberOfAppliances; }

Appliance::Appliance(const String &description, const String &brand,
                     float power) {
  assign(description, brand, power);
  generateSerialNumber();
}

Appliance::Appliance(std::istream &file)
    : description{file, ','}, brand{file, ','} {
  file >> power;
  handleInputErrors(file);
  if (power <= 0)
    throw "невалидна стойност за мощност на уред: не може да е отрицателна или "
          "нула";

  file.ignore();

  generateSerialNumber();
}

Appliance::Appliance(const Appliance &other)
    : Appliance(other.description, other.brand, other.power) {}

Appliance &Appliance::operator=(const Appliance &other) {
  if (&other != this) {
    assign(other.description, other.brand, other.power);
  }
  return *this;
}

Appliance::~Appliance() {
  if (splitter)
    splitter->unplugAppliance(*this);
}

bool Appliance::setPower(float power) {
  if (power <= 0)
    throw "невалидна стойност за мощност на уред: не може да е отрицателна или "
          "нула";

  if (isPluggedIn())
    return false;

  this->power = power;
  return true;
}

void Appliance::plugIn(Splitter &splitter) { this->splitter = &splitter; }

void Appliance::unplug() {
  turnOff();
  this->splitter = nullptr;
}

bool Appliance::turnOn() {
  if (!isPluggedIn())
    return false;

  this->turnedOn = true;

  splitter->handlePotentialOutOfOrderSituation();

  return true;
}

void Appliance::turnOff() { this->turnedOn = false; }

void Appliance::print() const {
  std::cout << "Описание на уреда: ";
  description.print();
  std::cout << std::endl;
  std::cout << "Марка на уреда: ";
  brand.print();
  std::cout << std::endl;
  std::cout << "Мощност на уреда: " << power << " ампера" << std::endl;
  std::cout << "Състояние на уреда спрямо мрежата: ";
  if (isPluggedIn())
    std::cout << "включено";
  else
    std::cout << "изключено";
  std::cout << std::endl;
  std::cout << "Състояние на активност на уреда: ";
  if (turnedOn)
    std::cout << "включено";
  else
    std::cout << "изключено";
  std::cout << std::endl;
  std::cout << "Сериен номер на уреда: " << serialNumber << std::endl;
  std::cout << std::endl;
}

Splitter::Splitter(unsigned int numberOfSockets, float maxPower)
    : numberOfSockets{numberOfSockets}, maxPower{maxPower},
      sockets{new Appliance *[numberOfSockets]} {
  if (maxPower <= 0)
    throw "невалидна стойност за максимална мощност на разклонител: не може да "
          "е отрицателна или нула";
}

Splitter::Splitter(const Splitter &other)
    : Splitter{other.numberOfSockets, other.maxPower} {}

Splitter &Splitter::operator=(const Splitter &other) {
  if (&other != this) {
    if (other.numberOfSockets > numberOfSockets)
      throw "разклонителят, който искаме да присвоим, е с по-голям брой "
            "гнезда";

    maxPower = other.maxPower;

    numberOfAppliances = other.numberOfAppliances;
    for (unsigned int i{0}; i < numberOfAppliances; i++)
      sockets[i] = other.sockets[i];

    for (unsigned int i{other.numberOfAppliances}; i < numberOfSockets; i++)
      sockets[i] = nullptr;
  }
  return *this;
}

Splitter::~Splitter() { delete[] sockets; }

float Splitter::getCurrentPower() const {
  float currentPower{0};
  for (unsigned int i{0}; i < numberOfAppliances; i++)
    if (sockets[i]->isTurnedOn())
      currentPower += sockets[i]->getPower();
  return currentPower;
}

void Splitter::handlePotentialOutOfOrderSituation() {
  if (getCurrentPower() > getMaxPower()) {
    outOfOrder = true;
    for (unsigned int i{0}; i < numberOfAppliances; i++) {
      sockets[i]->unplug();
      sockets[i] = nullptr;
    }
    numberOfAppliances = 0;
    throw "разклонителят изгоря";
  }
}

bool Splitter::plugApplianceIn(Appliance &appliance) {
  if (outOfOrder)
    return false;

  if (numberOfAppliances >= numberOfSockets)
    return false;

  sockets[numberOfAppliances++] = &appliance;
  appliance.plugIn(*this);

  return true;
}

bool Splitter::unplugAppliance(Appliance &appliance) {
  for (unsigned int i{0}; i < numberOfAppliances; i++) {
    if (sockets[i] == &appliance) {
      appliance.unplug();
      sockets[i] = nullptr;
      numberOfAppliances--;
      return true;
    }
  }

  return false;
}

void Splitter::print() const {
  std::cout << "Брой гнезда в разклонителя: " << numberOfSockets << std::endl;
  std::cout << "Максимално допустим ток в разклонителя: " << maxPower
            << " ампера" << std::endl;
  std::cout << "Текущо използван ток от разклонителя: " << getCurrentPower()
            << " ампера" << std::endl;

  std::cout << "Включени уреди в разклонителя:" << std::endl;
  for (unsigned int i{0}; i < numberOfAppliances; i++) {
    sockets[i]->print();
  }

  std::cout << std::endl;
}

Appliances::Appliances(unsigned int numberOfAppliances)
    : numberOfAppliances{numberOfAppliances},
      appliances{new Appliance *[numberOfAppliances]} {}

Appliances::~Appliances() {
  for (unsigned int i{0}; i < numberOfAppliances; i++)
    delete appliances[i];
  delete[] appliances;
}

Appliance *Appliances::getAppliance(unsigned int index) {
  if (index >= currentNumberOfAppliances)
    return nullptr;

  return appliances[index];
}

bool Appliances::addAppliance(Appliance &appliance) {
  if (currentNumberOfAppliances >= numberOfAppliances)
    return false;

  appliances[currentNumberOfAppliances++] = &appliance;
  return true;
}

int main() {
  try {
    unsigned int n;
    std::cout << "Въведете броя гнезда в разклонителя: ";
    std::cin >> n;
    handleInputErrors(std::cin);
    std::cin.ignore();

    float i;
    std::cout << "Въведете максимално допустимия ток в разклонителя в ампери: ";
    std::cin >> i;
    handleInputErrors(std::cin);
    std::cin.ignore();

    Splitter splitter{n, i};

    std::cout << "Въведете име на файл, откъдето да се прочетат включените "
                 "уреди в разклонителя: ";
    String filename{std::cin};
    std::ifstream file{filename.getData()};
    if (!file.is_open())
      throw "неуспешен опит за отваряне на файла с уредите, включени в "
            "разклонителя";

    unsigned int numberOfAppliances;
    file >> numberOfAppliances;
    handleInputErrors(file);
    file.ignore();

    Appliances appliances{n};
    for (unsigned int i{0}; i < numberOfAppliances; i++) {
      appliances.addAppliance(*new Appliance{file});
    }

    for (unsigned int i{numberOfAppliances}; i < n; i++) {
      appliances.addAppliance(
          *new Appliance{*appliances.getAppliance(i - numberOfAppliances)});
    }
    for (unsigned int i{0}; i < n; i++) {
      splitter.plugApplianceIn(*appliances.getAppliance(i));
    }
    for (unsigned int i{0}; i < n; i++) {
      appliances.getAppliance(i)->turnOn();
    }
  } catch (const char *error) {
    std::cerr << "грешка: " << error << std::endl;
  }

  return 0;
}
