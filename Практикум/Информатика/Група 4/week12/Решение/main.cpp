#include <iostream>
#include <memory>
#include <cassert>
#include "SpecificAnimals.h"

void printAnimalStatus(const Animal& animal) {
    std::cout << "\nAnimal status:\n";
    std::cout << animal;
    std::cout << "------------------------\n";
}

bool testFeeding(Animal& animal, const Food& food) {
    std::cout << "\nAttempting to feed with " << food.getName() << ":\n";
    bool result = animal.feed(food);
    if (result) {
        std::cout << "Successful feeding!\n";
    } else {
        std::cout << "The animal cannot eat this food.\n";
    }
    printAnimalStatus(animal);
    return result;
}

void testAttack(Animal& attacker, Animal& target) {
    std::cout << "\n" << attacker.getName() << " attacks " << target.getName() << ":\n";
    std::cout << "Before the attack:\n";
    printAnimalStatus(target);
    
    attacker.attack(target);
    
    std::cout << "After the attack:\n";
    printAnimalStatus(target);
}

int main() {
    Lion lion("Simba");
    Dragon dragon("Drake");
    Eagle eagle("Eagle");
    Scorpion scorpion("Scorpion");
    Chimera chimera("Chimera");
    Griffin griffin("Griffin");
    Manticore manticore("Manticore");

    std::cout << lion<< std::endl;
    std::cout << dragon<< std::endl;
    std::cout << eagle<< std::endl;
    std::cout << scorpion<< std::endl;
    std::cout << chimera<< std::endl;
    std::cout << griffin<< std::endl;
    std::cout << manticore<< std::endl;

    Beef beef;
    Pork pork;
    Banana banana;
    Apple apple;
    Strawberry strawberry;
    FruitSalad fruitSalad;
    MixedMeal mixedMeal;

    std::cout << beef<< std::endl;
    std::cout << pork<< std::endl;
    std::cout << banana<< std::endl;
    std::cout << apple<< std::endl;
    std::cout << strawberry<< std::endl;
    std::cout << fruitSalad<< std::endl;
    std::cout << mixedMeal<< std::endl;

    std::cout << "=== Feeding Test ===\n";
    assert(testFeeding(lion, beef));
    assert(!testFeeding(lion, banana));
    assert(testFeeding(dragon, beef));
    assert(testFeeding(dragon, banana));
    assert(!testFeeding(eagle, beef));
    assert(testFeeding(eagle, banana));
    assert(testFeeding(chimera, beef));
    assert(testFeeding(griffin, banana));
    assert(testFeeding(manticore, mixedMeal));

    std::cout << "\n=== Attack Test ===\n";
    int health = lion.getBloodCells();
    testAttack(dragon, lion);
    assert(lion.getBloodCells() == health / 2);

    int health_scorpion = scorpion.getBloodCells();
    testAttack(eagle, scorpion);
    assert(scorpion.getBloodCells() == health_scorpion - 20);

    int health_eagle = eagle.getBloodCells();
    testAttack(scorpion, eagle);
    assert(eagle.getBloodCells() == health_eagle - 50);

    int health_dragon = dragon.getBloodCells();
    testAttack(chimera, dragon);
    assert(dragon.getBloodCells() == health_dragon - 100 - 20);

    int health_chimera = griffin.getBloodCells();
    testAttack(griffin, chimera);
    assert(chimera.getBloodCells() == health_chimera - 30);

    int health_griffin = griffin.getBloodCells();
    testAttack(manticore, griffin);
    assert(griffin.getBloodCells() == health_griffin - 100);

    return 0;
} 