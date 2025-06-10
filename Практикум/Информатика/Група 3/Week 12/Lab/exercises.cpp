#include <iostream>

#include <cstring>



class Animal {
public:
    Animal() {
        this->name = new char[1];
        
        this->name[0] = '\0';
    }

    Animal(const char* name) {
        if (name == nullptr || name[0] == '\0') {
            throw std::invalid_argument("Invalid Argument!");
        }

        this->name = new char[strlen(name) + 1];

        strcpy(this->name, name);
    }

    Animal(const Animal& other) {
        this->name = new char[strlen(other.name) + 1];

        strcpy(this->name, other.name);
    }

    Animal& operator=(const Animal& other) {
        if (this != &other) {
            char* buffer = new char[strlen(other.name) + 1];

            strcpy(buffer, other.name);

            delete[] this->name;

            this->name = buffer;
        }

        return *this;
    }

    const char* getName() const { return this->name; }

    virtual void eat() {
        std::cout << "I am Animal, who is eating!" << std::endl;
    }

    void print() const {
        std::cout << "&Animal = " << this << std::endl;
    }

    // virtual void print() const = 0;

    virtual ~Animal() {
        delete[] this->name;
    }

private:
    // const char* name1;
    // 
    const char* name2;

    char* name;
};




class WingedAnimal : virtual public Animal {
public:
    WingedAnimal() = default;
    WingedAnimal(const char* name, int wings) : Animal(name), wings(wings) {}

    WingedAnimal& operator=(const WingedAnimal& other) = default;

    void print() const {
        Animal::print();
        std::cout << "The wings is: " << wings      << std::endl;
        std::cout << "&WingedAnimal" << this << std::endl;
    }

    virtual void eat() {
        std::cout << "I am WingedAnimal, who is eating!" << std::endl;
    }

    virtual ~WingedAnimal() {}

private:
    // Тук беше const int, но при оператора за присвояване,
    // ни даваше грешка, че методът WingedAnimal::operator=
    // е изтрит, въпреки че горе е с default иплементация.

    int wings;
};




class Mammal : virtual public Animal {
public:
    Mammal() = default;
    Mammal(const char* name, int years) : Animal(name), years(years) {}

    void print() const {
        Animal::print();
        std::cout << "The years are: " << years << std::endl;
        std::cout << "&Mammal" << this << std::endl;
    }

    virtual ~Mammal() {}

private:
    int years;
};




/* class SpecialMammal : public Mammal {
public:
    SpecialMammal() : Mammal() {}
}; */




class Bat : public WingedAnimal, public Mammal {
public:
    /* Bat() : WingedAnimal(), Mammal() {
        WingedAnimal::print();
    } */

    Bat() = default;

    Bat(const char* name, const char* virus, int wings, int years) : Animal(name), WingedAnimal(name, wings), Mammal(name, years) {
        this->virus = new char[strlen(virus) + 1];

        strcpy(this->virus, virus);
    }

    Bat(const Bat& other) : Animal(other), WingedAnimal(other), Mammal(other) {
        this->virus = new char[strlen(other.virus) + 1];

        strcpy(this->virus, other.virus);
    }

    Bat& operator=(const Bat& other) {
        if (this != &other) {
            Animal::operator=(other);

            WingedAnimal::operator=(other);
            Mammal::operator=(other);

            char* buffer = new char[strlen(other.virus) + 1];

            strcpy(buffer, other.virus);

            delete[] this->virus;

            this->virus = buffer;
        }

        return *this;
    }

    ~Bat() {
        delete[] virus;
    }

    const char* getVirus() const { return this->virus; }

    void print() const {
        WingedAnimal::print();
        Mammal::print();
        std::cout << "&Bat" << this << std::endl;
    }

    void eat() {
        std::cout << "I am the bad Bat!" << std::endl;
    }

private:
    char* virus;
};



void callEatFunction(Animal* animal) {
    animal->eat();
}



int main() {
    /* Bat instance("COVID19");

    std::cout << instance.getVirus() << std::endl;
    std::cout << instance.getName() << std::endl; */

    // std::cout << strlen(nullptr) << std::endl;

    Bat instance("Batman", "COVID19", 20, 70);

    std::cout << instance.getName() << std::endl;
    std::cout << instance.getVirus() << std::endl;

    Bat copyBat(instance);

    copyBat.print();

    instance = copyBat;

    instance.print();
    
    // WingedAnimal animal("Name", 90);

    // Bat bat("Name", "COVID", 90, 80);

    // bat.eat();


    Animal* animal = new Animal("Animal Name");
    WingedAnimal* winged = new WingedAnimal("Winged Animal Name", 20);
    Bat* bat = new Bat("BatMan", "COVID26", 90, 90);

    callEatFunction(bat);
    bat->print();

    delete animal;
    delete winged;
    delete bat;


    return 0;
}