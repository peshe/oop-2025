#include <iostream>

#include "DynamicArray.h"

int main() 
{
	DynamicArray<int> a;
	a.add(5);
	a.add(7);
	a.add(1);
	a *= 2;
	try 
	{
		std::cout << a[123];
	}
	catch (std::out_of_range e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	std::cout << a << std::endl;
	std::cout << a * 2 << std::endl;
	std::cout << a * 3 << std::endl;
	std::cout << a * 0 << std::endl;

	DynamicArray<int>::Iterator it = a.getIterator();
	while (it.hasNext())
	{
		std::cout << it.next() << std::endl;
	}
}