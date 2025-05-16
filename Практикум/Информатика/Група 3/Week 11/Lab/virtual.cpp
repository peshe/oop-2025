#include <cstring>
#include <iostream>

class Interface {
public:
  virtual ~Interface() {}

  virtual void f(int x) = 0;

  virtual Interface *clone() = 0;
};

class Base : public Interface {
protected:
  int a;

public:
  Base(int a) : a{a} {}

  void f(int x) override {
    std::cout << "Base(" << a << ").f(" << x << ")" << std::endl;
  }
};

class Derived : public Base {
protected:
  float b;

public:
  Derived(int a, float b) : Base{a}, b{b} {}

  void f(int x) override {
    std::cout << "Derived(" << a << ", " << b << ").f(" << x << ")"
              << std::endl;
  }

  Interface *clone() override { return new Derived{*this}; }
};

class MoreDerived : public Derived {
protected:
  char c;

public:
  MoreDerived(int a, float b, char c) : Derived{a, b}, c{c} {}

  void f(int x) override {
    std::cout << "MoreDerived(" << a << ", " << b << ", " << c << ").f(" << x
              << ")" << std::endl;
  }

  Interface *clone() override { return new MoreDerived{*this}; }
};

int main() {
  Derived *der{new Derived{1, 0.5}};
  Base *derBasePtr{der};
  derBasePtr->f(5);
  Base &derBaseRef{*der};
  derBaseRef.f(6);
  delete derBasePtr;

  MoreDerived *moreDer{new MoreDerived{2, 3.4, 'a'}};
  Base *moreDerBase{moreDer};
  moreDerBase->f(7);
  moreDerBase->Base::f(8);

  Derived *moreDerDer{moreDer};
  moreDerDer->f(9);

  Interface *moreDerIface{moreDer};
  Interface *moreDerIfaceClone{moreDerIface->clone()};

  delete moreDerIfaceClone;
  delete moreDerIface;

  return 0;
}
