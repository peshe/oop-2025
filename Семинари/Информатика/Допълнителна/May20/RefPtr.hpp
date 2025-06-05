#include <iostream>

using std::cout;
using std::endl;

template<typename T> T minimum(T a, T b)
{
    return a<b ? a : b;
}


class RefCounted
{
    size_t refs = 0;
    public:
    size_t incRef() { cout << "I" << endl; return ++refs; }
    size_t decRef() { cout << "D" << refs << endl; --refs; return refs; }
    virtual ~RefCounted() {}
};



template<typename T> class RefPtr
{

    T * p = 0;

public:

    RefPtr() {}
    RefPtr(T * p) : p(p) {  p->incRef(); }

    RefPtr(RefPtr<T> const & r) : p(r.p)
    {
        cout << "R(R)" << endl;
        p->incRef(); 
    }

    RefPtr& operator=(RefPtr<T> const & r) 
    {
        cout << "R=" << endl;
        if(this != &r)
        {
            if(p)
            {
                size_t n = p->decRef();
                if(0 == n)
                    delete p;
            }

            p = r.p;

            r.p->incRef();

        }
        return *this;
    }

    T & operator*() {  return *p;  }
    T * operator->() {  return p;  }

    ~RefPtr()
    {
        if(p)
        {
            size_t n = p->decRef();
            if(0==n)
                delete p;
        }
    }

};


