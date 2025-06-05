#include <iostream>
#include "auto_ptr.hpp"

static void test1()
{
    AutoPtr<int> ptr(new int(10));
    std::cout << *ptr << std::endl;

    int* p = new int[20];
    AutoPtr<int> ptr2(p);

    std::cout<< *ptr2 << std::endl;
}

static void test2()
{
    struct A
    {
        AutoPtr<int> ptr1;
        A() = default;
        A(int p) : ptr1(new int(p)) {}

        void print() const
        {
            if (ptr1) std::cout << *ptr1;
            else std::cout << "null";
        }
    };

    AutoPtr<A> ptr1(new A(10));
    ptr1->print();
//    AutoPtr<A> ptr2(ptr1);
    AutoPtr<A> ptr3(std::move(ptr1));
    ptr3->print();
    if (ptr1) ptr1->print();
    else std::cout << "Moved is: " << ptr1 << "\n";
}

struct DebugDel
{
    void free(int* ptr) { 
        std::cout << "Deleting " << ptr << "\n";
        delete ptr;
    }
};

static void test3()
{
    {
        std::cout << 0;
        AutoPtr<int, DebugDel> ptr(new int(10));
        std::cout << 1;
    }
    std::cout << 2;
    AutoPtr<int, DebugDel> ptr(new int(3));
    std::cout << *ptr << "\n";
    ptr.reset(nullptr);
    std::cout << (bool)ptr << "\n";
    int* arr = new int [5] {1, 2, 3, 4, 5};
    ptr = arr;
    std::cout << *ptr << "\n";
}

void ctest1()
{
    CountingPtr<int> ptr1(new int(42));
    CountingPtr<int> ptr2(ptr1);
    CountingPtr<int> ptr3(std::move(ptr2));
    std::cout << *ptr3 << "\n";
    *ptr1 = 10;
    std::cout << *ptr3 << "\n";
}

void ctest2()
{
    CountingPtr<int, DebugDel> ptr1(new int(42));
    CountingPtr<int, DebugDel> ptr2(ptr1);
    {
        CountingPtr<int, DebugDel> ptr3(ptr1);
        ptr1.reset();
    }
    {
        CountingPtr<int, DebugDel> p4(std::move(ptr1));
    }
}


int main()
{
    //test1();
    //test2();
    //test3();

    ctest1();
    ctest2();

    return 0;
}
