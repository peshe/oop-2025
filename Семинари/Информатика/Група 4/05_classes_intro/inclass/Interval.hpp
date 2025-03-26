#pragma once
class Interval
{
	int a;
	int b;

public:
	Interval();
	Interval(int a, int b);

	int getA() const;
	int getB() const;

	unsigned getLength() const;

	// Checks whether the number is in the interval
	bool isInInterval(int number) const;

	unsigned getPrimeCount() const;
	unsigned getPalindromeCount() const;

	bool areABpowersOf2() const;

	Interval intersect(const Interval& other) const;

private:
	unsigned getPredicateCount(bool (*predicate)(int)) const;

	bool checkA(bool (*predicate)(int)) const;
	bool checkB(bool (*predicate)(int)) const;
};

