#include "polynomial.hpp"
#include <exception>
#include <cassert>

Polynomial::Polynomial(double coef)
    : coef(new double[1])
    , power(0), size(1)
{
    this->coef[0] = coef;
}

Polynomial::Polynomial(double* coefs, unsigned power)
    : coef(nullptr)
    , power(power)
    , size(power+1)
{
    if (!coefs) 
        throw std::invalid_argument("Coeficients must not be null!\n");
    this->coef = new double[power+1];
    for (unsigned i = 0; i <= power; ++i) {
        this->coef[i] = coefs[i];
    }
    normalize();
}

Polynomial::Polynomial(double coef, unsigned power)
    :coef(new double[power + 1] {})
    , power(power)
    , size(power+1)
{
    this->coef[power] = coef;
}

Polynomial::Polynomial(const Polynomial& other)
    : coef(new double[other.power + 1])
    , power(other.power)
    , size(other.power + 1)
{
    for (unsigned i = 0; i <= power; ++i) {
        this->coef[i] = other.coef[i];
    }
}

Polynomial::Polynomial(Polynomial&& other) noexcept
    : coef(other.coef)
    , power(other.power)
    , size (other.size)
{
    other.coef = nullptr;
    other.size = 0;
}

Polynomial::~Polynomial() noexcept
{
    delete[] coef;
}

Polynomial& Polynomial::operator=(const Polynomial& other)
{
    if (&other != this) {
        resize(other.power + 1);
        for (unsigned i = 0; i <= other.power; ++i) {
            coef[i] = other.coef[i];
        }
        power = other.power;
    }
    return *this;
}

Polynomial& Polynomial::operator=(Polynomial&& other) noexcept
{
    std::swap(coef, other.coef);
    power = other.power;
    size = other.size;
    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& other)
{
    unsigned resPower = std::max(power, other.power);
    resize(resPower+1);
    
    for (unsigned i = 0; i <= resPower; ++i) {
        coef[i] += other[i];
    }

    power = resPower;
    normalize();
    return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& other)
{
    *this *= -1;
    *this += other;
    *this *= -1;
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& other)
{
    unsigned long long resPower = power * other.power;
    assert(resPower == (power * other.power));
    double* newCoef = new double[resPower + 1] {};

    for (unsigned i = 0; i <= power; ++i) {
        for (unsigned j = 0; j <= other.power; ++j) {
            newCoef[i + j] += coef[i] * other.coef[j];
        }
    }
    delete[] coef;
    coef = newCoef;
    power = (unsigned)resPower;
    normalize();
    return *this;
}

Polynomial& Polynomial::operator*=(double c) noexcept
{
    if (abs(c) < Polynomial::eps) {
        coef[0] = 0;
        power = 0;
    }
    else {
        for (unsigned i = 0; i <= power; ++i) {
            coef[i] *= c;
        }
    }
    return *this;
}

Polynomial Polynomial::operator-() const
{
    return Polynomial(*this) *= -1;
}

Polynomial::operator bool() const noexcept
{
    return !isZero();
}

bool Polynomial::operator!() const noexcept
{
    return isZero();
}

Polynomial& Polynomial::operator++()
{
    resize(power + 2);
    for (unsigned i = power + 1; i > 0; --i) {
        coef[i] = coef[i - 1] / i;
    }
    ++power;
    coef[0] = 0; // No const :)
    return *this;
}

Polynomial Polynomial::operator++(int)
{
    Polynomial res(*this);
    ++(*this);
    return res;
}

Polynomial& Polynomial::operator--()
{
    for (unsigned i = 0; i < power; ++i) {
        coef[i] = coef[i+1]*(i+1);
    }
    --power;
    return *this;
}

Polynomial Polynomial::operator--(int)
{
    Polynomial res(*this);
    --(*this);
    return res;
}

double Polynomial::operator[](unsigned index) const
{
    if (index > power) return 0.0;
    return coef[index];
}

double& Polynomial::operator[](unsigned index)
{
    assert(index <= power);
    // Here is a problem ...
    return coef[index];
}

double& Polynomial::at(unsigned index)
{
    if (index > power) throw std::out_of_range("Invalid index!");
    // Here is a problem also ...
    return (*this)[index];
}

double Polynomial::operator()(double x) const noexcept
{
    double res = coef[0];
    double xPowered = 1;
    for (unsigned p = 1; p <= power; ++p) {
        xPowered *= x;
        res += coef[p] * xPowered;
    }
    return res;
}

unsigned Polynomial::getPower() const noexcept
{
    return power;
}

void Polynomial::normalize() noexcept
{
    while (power > 0 && abs(coef[power]) < Polynomial::eps)
        --power;
}

bool Polynomial::isZero() const noexcept
{
    return power == 0 && abs(coef[0]) < Polynomial::eps;
}

void Polynomial::resize(unsigned newSize)
{
    if (newSize <= size) return;

    double* newCoef = new double[newSize] {};
    for (unsigned i = 0; i <= power; ++i)
        newCoef[i] = coef[i];
    delete[] coef;
    coef = newCoef;
    size = newSize;
}

bool operator==(const Polynomial& p1, const Polynomial& p2)
{
    if (p1.getPower() != p2.getPower())
        return false;
    for (unsigned p = 0; p <= p1.getPower(); ++p) {
        if (abs(p1[p] - p2[p]) > Polynomial::eps)
            return false;
    }
    return true;
}

bool operator!=(const Polynomial& p1, const Polynomial& p2)
{
    return !(p1 == p2);
}

bool operator<(const Polynomial& p1, const Polynomial& p2)
{
    return p1.getPower() < p2.getPower();
}

bool operator>(const Polynomial& p1, const Polynomial& p2)
{
    return p2 < p1;
}

bool operator<=(const Polynomial& p1, const Polynomial& p2)
{
    return p1 < p2 || p1 == p2;
}

bool operator>=(const Polynomial& p1, const Polynomial& p2)
{
    return p2 <= p1;
}

Polynomial operator+(const Polynomial& p1, const Polynomial& p2)
{
    Polynomial res(p1);
    return res += p2;
}

Polynomial operator-(const Polynomial& p1, const Polynomial& p2)
{
    Polynomial res(p1);
    return res -= p2;
}

Polynomial operator*(const Polynomial& p1, const Polynomial& p2)
{
    Polynomial res(p1);
    return res *= p2;
}

Polynomial operator*(const Polynomial& p, double coef)
{
    Polynomial res(p);
    return res *= coef;
}

Polynomial operator*(double coef, const Polynomial& p)
{
    return p * coef;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p)
{
    os << p[p.getPower()];
    for (long long int pow = (long long int)p.getPower(); pow >= 0; --pow) {
        double coef = p[(unsigned)pow];
        if (pow < p.getPower())
            os << (coef >= 0 ? "+" : "-") << abs(coef);
        os << "X^" << pow;
    }
    return os;
}

static bool readOne(std::istream& is, Polynomial& p)
{
    double coef;
    unsigned power;
    char symbol;

    is >> coef >> symbol;
    if (symbol != 'X' && symbol != 'x') is.setstate(std::ios::failbit);
    is >> symbol;
    if (symbol != '^') is.setstate(std::ios::failbit);
    is >> power;
    if (is){
        p = Polynomial(coef, power);
    }
    return (bool)is;
}

std::istream& operator>>(std::istream& is, Polynomial& p)
{
    if (!is) return is;

    Polynomial res, one;
    do {
        if (readOne(is, one))
            res += one;
    } while (is && one.getPower() > 0);

    if (is) p = std::move(res);
    return is;
}

const double Polynomial::eps = 1e-7;
