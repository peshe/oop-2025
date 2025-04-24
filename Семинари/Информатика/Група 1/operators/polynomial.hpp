#pragma once

#include <iostream>

class Polynomial
{
public:
    Polynomial(double value = 0.0);
    Polynomial(double* coefs, unsigned power);
    Polynomial(double coef, unsigned power);
    Polynomial(const Polynomial&);
    Polynomial(Polynomial&&) noexcept;

    ~Polynomial() noexcept;
    
    Polynomial& operator=(const Polynomial&);
    Polynomial& operator=(Polynomial&&)noexcept;

    Polynomial& operator+=(const Polynomial&);
    Polynomial& operator-=(const Polynomial&);
    Polynomial& operator*=(const Polynomial&);
    Polynomial& operator*=(double coef) noexcept;
    
    Polynomial operator-() const;

    operator bool() const noexcept;
    bool operator!() const noexcept;

    Polynomial& operator++();
    Polynomial operator++(int);

    Polynomial& operator--();
    Polynomial operator--(int);

    double operator[](unsigned index) const;
    double& operator[](unsigned index);
    double& at(unsigned index);

    double operator()(double x) const noexcept;

    unsigned getPower() const noexcept;

private:
    void normalize() noexcept;
    bool isZero() const noexcept;

    void resize(unsigned newSize);

private:
    double* coef;
    unsigned power;
    unsigned size;

public:
    static const double eps;
};

bool operator==(const Polynomial& p1, const Polynomial& p2);
bool operator!=(const Polynomial& p1, const Polynomial& p2);

bool operator<(const Polynomial& p1, const Polynomial& p2);
bool operator<=(const Polynomial& p1, const Polynomial& p2);
bool operator>(const Polynomial& p1, const Polynomial& p2);
bool operator>=(const Polynomial& p1, const Polynomial& p2);

Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
Polynomial operator-(const Polynomial& p1, const Polynomial& p2);
Polynomial operator*(const Polynomial& p1, const Polynomial& p2);
Polynomial operator*(const Polynomial& p, double coef);
Polynomial operator*(double coef, const Polynomial& p);

std::ostream& operator<<(std::ostream& os, const Polynomial& p);
std::istream& operator>>(std::istream& is, Polynomial& p);
