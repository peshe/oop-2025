#include <iostream>
#include <cstdlib> // std::abs

struct Fraction
{
	long long num;
	long long den;
};

long long gcd(long long a, long long b)
{
	a = std::abs(a);
	b = std::abs(b);
	while(a && b)
		a > b ? a %= b : b %= a;
	return a | b;
}

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
}
