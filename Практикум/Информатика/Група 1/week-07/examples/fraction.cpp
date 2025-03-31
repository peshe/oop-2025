#include <iostream>
#include <cstdlib> // std::abs

long long gcd(long long a, long long b)
{
	a = std::abs(a);
	b = std::abs(b);
	while(a && b)
		a > b ? a %= b : b %= a;
	return a | b;
}

class Fraction
{
	long long num;
	long long den;

	void reduce()
	{
		long long gcd_val = gcd(num, den);
		num /= gcd_val;
		den /= gcd_val;
	}
public:
	Fraction(long long num = 0, long long den = 1)
	{
		if(den == 0)
			throw "division by zero";
		if(den < 0)
		{
			num = -num;
			den = -den;
		}
		this->num = num;
		this->den = den;
		reduce();
	}

	Fraction negate() const
	{
		return Fraction(-num, den);
	}
	Fraction reciproc() const
	{
		return Fraction(den, num);
	}
	Fraction add(const Fraction& rhs) const
	{
		return Fraction(/*this->*/num * rhs.den + den * rhs.num, den * rhs.den);
	}
	Fraction subtract(const Fraction& rhs) const
	{
		return /*this->*/add(rhs.negate());
	}
	Fraction multiply(const Fraction& rhs) const
	{
		return Fraction(num * rhs.num, den * rhs.den);
	}
	Fraction divide(const Fraction& rhs) const
	{
		return multiply(rhs.reciproc());
	}

	void print() const
	{
		std::cout << num;
		if(den != 1)
			std::cout << '/' << den;
	}
};

/*
void f(long long d)
{
	try{
		Fraction f(5, 0);
		f.print();
	}
	catch(int n)
	{
		std::cerr << n << '\n';
	}
	catch(const char* msg)
	{
		std::cerr << msg << '\n';
	}
	std::cout << "continuing f()...\n";
	Fraction f(6, d);
	f.print();
	std::cout << "exiting f()...\n";
}
*/

Fraction read_fraction()
{
	long long num, den;
	std::cin >> num >> den;
	Fraction f(num, den);
	return f;
}

int main()
{
	/*try
	{
		f(0);
	}
	catch(const char* msg)
	{
		std::cerr << "from main: catch(const char*): " << msg << '\n';
		return 1;
	}*/

	try
	{
		Fraction a = read_fraction(), b = read_fraction();
		std::cout << "a + b = ";
		a.add(b).print();
		std::cout << '\n';

		std::cout << "a - b = ";
		a.subtract(b).print();
		std::cout << '\n';

		std::cout << "a * b = ";
		a.multiply(b).print();
		std::cout << '\n';

		std::cout << "a / b = ";
		a.divide(b).print();
		std::cout << '\n';
	}
	catch(const char* msg)
	{
		std::cerr << msg << '\n';
		return 1;
	}

	return 0;
}
