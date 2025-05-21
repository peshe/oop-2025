#ifndef SPECIFIC_ANIMALS_H
#define SPECIFIC_ANIMALS_H

#include "Animal.h"

class Lion : public virtual Animal {
public:
    explicit Lion(const char* name);
    void roar();
    void attack(Animal& target) override;
    bool feed(const Food& food) override;
};

class Dragon : public virtual Animal {
public:
    explicit Dragon(const char* name);
    void fire(Animal& target);
    void attack(Animal& target) override;
};

class Eagle : public virtual Animal {
public:
    explicit Eagle(const char* name);
    void fly(Animal& target);
    void attack(Animal& target) override;
};

class Scorpion : public virtual Animal {
public:
    explicit Scorpion(const char* name);
    void poison(Animal& target);
    void attack(Animal& target) override;
};

class Chimera : public virtual Dragon, public virtual Lion {
public:
    explicit Chimera(const char* name);
    void attack(Animal& target) override;
    bool feed(const Food& food) override;
};

class Griffin : public virtual Lion, public virtual Eagle {
public:
    explicit Griffin(const char* name);
    void attack(Animal& target) override;
    bool feed(const Food& food) override;
};

class Manticore : public virtual Eagle, public virtual Lion, public virtual Scorpion {
public:
    explicit Manticore(const char* name);
    void attack(Animal& target) override;
    bool feed(const Food& food) override;
};

#endif