#include "Interval.hpp"
#include <cmath>

Interval::Interval() : Interval(0, 0) {}

Interval::Interval(int a, int b)
{
	if (a <= b) {
		this->a = a;
		this->b = b;
	}
	else
	{
		this->a = this->b = 0;
	}
}

int Interval::getA() const {
	return this->a;
}

int Interval::getB() const {
	return this->b;
}

unsigned Interval::getLength() const
{
	return std::abs(a - b);
}

bool Interval::isInInterval(int number) const
{
	return this->a <= number && number <= this->b;
}

bool isPrime(int n) {
	if (n < 2) {
		return false;
	}

	const double root = std::sqrt(n);

	for (int i = 2; i <= root; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

int reverse(int n) {
	int reversed = 0;

	while (n != 0) {
		reversed = reversed * 10 + n % 10;
		n /= 10;
	}

	return reversed;
}

bool isPalindrome(int n) {
	return reverse(n) == n;
}

unsigned Interval::getPrimeCount() const
{
	return this->getPredicateCount(isPrime);
}

unsigned Interval::getPalindromeCount() const
{
	return this->getPredicateCount(isPalindrome);
}

bool Interval::areABpowersOf2() const
{
	return checkA(isPower2) && checkB(isPower2);
}

Interval Interval::intersect(const Interval& other) const
{
	return Interval(std::max(this->a, other.a), std::min(this->b, other.b));
}

unsigned Interval::getPredicateCount(bool(*predicate)(int)) const
{
	unsigned count = 0;
	for (int i = this->a; i <= this->b; ++i) {
		if (predicate(i)) {
			count++;
		}
	}
	return count;
}

bool Interval::checkA(bool(*predicate)(int)) const
{
	return predicate(this->a);
}

bool Interval::checkB(bool(*predicate)(int)) const
{
	return predicate(this->b);
}

bool isPower2(int n) {
	return false;
}
