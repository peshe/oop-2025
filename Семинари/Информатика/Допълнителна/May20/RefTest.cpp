#include "RefPtr.hpp"

struct S : public RefCounted
{
    int n = 0;

    S() { cout << "S::S()" << endl; }
    ~S() { cout << "S::~S()" << endl; }
    
};


void f(RefPtr<S> p)
{
    cout << "F" << endl;
    cout << p->n << endl;
}

int main()
{
    RefPtr<S> ptr = new S;

    RefPtr<S> ptr2 = ptr;

    ptr = ptr2;

    RefPtr<S> ptr3; 
    ptr3 = ptr;

    f(ptr3);

}