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

	operator double() const
	{
		return static_cast<double>(num) / den;
	}

	Fraction operator-() const
	{
		return Fraction(-num, den);
	}
	Fraction reciproc() const
	{
		return Fraction(den, num);
	}
	Fraction operator+(const Fraction& rhs) const
	{
		return Fraction(num * rhs.den + den * rhs.num, den * rhs.den);
	}
	Fraction operator-(const Fraction& rhs) const
	{
		return *this + (-rhs);
	}
	Fraction operator*(const Fraction& rhs) const
	{
		return Fraction(num * rhs.num, den * rhs.den);
	}
	Fraction operator/(const Fraction& rhs) const
	{
		return *this * rhs.reciproc();
	}
	bool operator==(const Fraction& rhs) const
	{
		return num == rhs.num && den == rhs.den;
	}
	bool operator!=(const Fraction& rhs) const
	{
		return !(*this == rhs);
	}
	bool operator<(const Fraction& rhs) const
	{
		return num * rhs.den < den * rhs.num;
	}
	bool operator<=(const Fraction& rhs) const
	{
		return !(rhs < *this);
	}
	bool operator>(const Fraction& rhs) const
	{
		return rhs < *this;
	}
	bool operator>=(const Fraction& rhs) const
	{
		return !(*this < rhs);
	}

	//friend Fraction operator+(const Fraction& a, const Fraction& b);
	//friend std::ostream& operator<<(std::ostream& os, const Fraction& f);

	long long Numerator() const
	{
		return num;
	}
	long long Denominator() const
	{
		return den;
	}

	static Fraction read()
	{
		long long num, den;
		std::cin >> num >> den;
		Fraction f(num, den);
		return f;
	}

	void print() const
	{
		std::cout << num;
		if(den != 1)
			std::cout << '/' << den;
	}
};

/*Fraction operator+(const Fraction& lhs, const Fraction& rhs)
{
	return Fraction(lhs.num * rhs.den + lhs.den * rhs.num, lhs.den * rhs.den);
}*/

std::ostream& operator<<(std::ostream& os, const Fraction& f)
{
	os << f.Numerator();
	if(f.Denominator() != 1)
		os << '/' << f.Denominator();
	return os;
}

void g(double a)
{
	std::cout << "g(): " << a << '\n';
}

int main()
{
	try
	{
		Fraction a = Fraction::read(), b = Fraction::read();

		std::cout << "a + b = " << a + b << '\n';
		std::cout << "a - b = " << a - b << '\n';
		std::cout << "a * b = " << a * b << '\n';
		std::cout << "a / b = " << a / b << '\n';
		std::cout << (double)a << std::endl;
		std::cout << static_cast<double>(a) << std::endl;
		g(a);

		std::cout << "a < b: " << (a < b) << '\n';
		std::cout << "a <= b: " << (a <= b) << '\n';
		std::cout << "a > b: " << (a > b) << '\n';
	}
	catch(const char* msg)
	{
		std::cerr << msg << '\n';
		return 1;
	}
	return 0;
}













































/*
Fraction normalize(Fraction a)
{
	long long gcd_val = gcd(a.num, a.den);
	a.num /= gcd_val;
	a.den /= gcd_val;
	return a;
}

bool add(Fraction a, Fraction b, Fraction& res)
{
	if(a.den == 0 || b.den == 0)
		return false;
	res.num = a.num * b.den + a.den * b.num;
	res.den = a.den * b.den;
	res = normalize(res);
	return true;
}

bool divide(Fraction a, Fraction b, Fraction& res)
{
	if(a.den == 0 || b.den == 0 || b.num == 0)
		return false;
	res.num = ...;
	res.den = ...;
	res = normalize(res);
	return true;
}

void print(Fraction a)
{
	if(a.den == 0)
		std::cout << "Invalid fraction";
	std::cout << a.num;
	if(a.den != 1)
		std::cout << '/' << a.den;
}

void read(Fraction& a)
{
	std::cin >> a.num >> a.den;
}

int main()
{
	Fraction a, b;
	read(a); read(b);

	Fraction sum;
	if(add(a, b, sum))
	{
		print(a);
		std::cout << " + ";
		print(b);
		std::cout << " = ";
		print(sum);
		std::cout << '\n';
	}

	return 0;
}*/