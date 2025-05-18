#include "bat.h"
#include "dog.h"
#include "eagle.h"
#include "penguin.h"

int main() {
  Animal *zoo[]{new Dog{"Rex"}, new Bat{"Bruce"}, new Eagle{"Aquila"},
                new Penguin{"Pingu"}};

  for (Animal *animal : zoo) {
    std::cout << "Animal name: " << animal->getName().getData() << std::endl;

    animal->eat();
    animal->breathe();
    animal->makeSound();
    animal->move();

    if (auto mammal{dynamic_cast<Mammal *>(animal)}) {
      std::cout << "Gestation: " << mammal->getGestationDays() << std::endl;
    }

    if (auto bird{dynamic_cast<Bird *>(animal)}) {
      std::cout << "Wingspan: " << bird->getWingSpan() << std::endl;

      try {
        bird->fly();
      } catch (const char *e) {
        std::cout << e << std::endl;
      }
    }
  }

  for (Animal *animal : zoo)
    delete animal;

  return 0;
}