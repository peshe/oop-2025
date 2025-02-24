#include <iostream>
#include <iomanip>

/* Structures (struct)
* A struct is a program-defined data type that allows us to bundle multiple variables together into a single type.

* A member in C++ is a variable, function, or type that belongs to a class type (structs, unions, classes).
	All members must be declared in the struct (or class) definition.

* The members of a struct are public by default, which means that they can be accessed from outside the struct.
* Data members (much like normal variables) are not initialized by default.

* The members of a struct can be accessed using the member selection operator (operator.).
	<struct_name>.<member_name>

* Members in the struct can be of any data type, including other structs.
*/

// Structure definition
struct Date {
	unsigned short day; // Uninitialized member - the value is undefined
	unsigned short month; // Uninitialized member - the value is undefined
	unsigned short year; // Uninitialized member - the value is undefined
};

struct Time {
	unsigned short hour = 0; // Initialized member - the value is 0
	unsigned short minute{}; // Initialized member - the value is 0
	unsigned short second{ 15 }; // Initialized member - the value is 15
};

constexpr int kMaxNameSize = 50;

struct Employee {
	int id{ 0 };
	char name[kMaxNameSize]{};
	double salary{ 1000.0 };

	Date hireDate{}; // A struct, can have another struct as a member
};

struct Point {
	int x;
	int y;
};

void printValueWithLeadingZeros(unsigned short value, int leadingZeroes = 2);
void printDate(const Date& date);
void printTime(const Time& time);
Point getZeroPoint1();
Point getZeroPoint2();
Point getZeroPoint3();

int main() {
	// Defining a struct object
	Date birthday; // struct created with undefined fields
	Time randomTime; // struct created with initialized fields

	// birthday refers to the entire struct object
	// To access a specific member we use the member selection operator (operator.)
	birthday.day = 17;
	birthday.month = 7;
	birthday.year = 2002;

	std::cout << "I was born on ";
	printDate(birthday);

	std::cout << "Random time: ";
	printTime(randomTime);

	// Struct initialization
	Date today = { 24, 2, 2025 };

	std::cout << "Today is ";
	printDate(today);

	// Another way to initialize a struct
	Time randomTime2{ 12, 30, 45 };

	std::cout << "Random time 2: ";
	printTime(randomTime2);

	// If the struct has members that have a default value, we can omit them
	// But we should not mix the order of the members
	Time randomTime3{ 12, 30 };

	std::cout << "Random time 3: ";
	printTime(randomTime3);

	// Const structs
	// The members of a const (or constexpr) struct cannot be modified
	const Date newYear{ 1, 1, 2025 };
	// newYear.day = 2; // Error: newYear is const

	// Employee struct
	Employee employee{ 1, "John Doe", 2000.0, { 1, 1, 2020 } };

	// Passing temporary structs
	printDate(Date { 23, 3, 2025 });
	// printDate({ 23, 3, 2025 }); - Struct type can be omitted

	// Returning a struct from a function
	Point zeroPoint1 = getZeroPoint1();
	Point zeroPoint2 = getZeroPoint2();
	Point zeroPoint3 = getZeroPoint3();

	std::cout << "Zero point 1: " << zeroPoint1.x << ", " << zeroPoint1.y << std::endl;
	std::cout << "Zero point 2: " << zeroPoint2.x << ", " << zeroPoint2.y << std::endl;
	std::cout << "Zero point 3: " << zeroPoint3.x << ", " << zeroPoint3.y << std::endl;

	return 0;
}

void printValueWithLeadingZeros(unsigned short value, int leadingZeroes) {
	std::cout << std::setw(leadingZeroes) << std::setfill('0') << value;
	std::cout << std::setw(0) << std::setfill(' ');
}

void printDate(const Date& date) {
	printValueWithLeadingZeros(date.day);
	std::cout << "/";
	printValueWithLeadingZeros(date.month);
	std::cout << '/';
	printValueWithLeadingZeros(date.year, 4);
	std::cout << std::endl;
}

void printTime(const Time& time) {
	printValueWithLeadingZeros(time.hour);
	std::cout << ":";
	printValueWithLeadingZeros(time.minute);
	std::cout << ":";
	printValueWithLeadingZeros(time.second);
	std::cout << std::endl;
}

Point getZeroPoint1() {
	Point temp{ 0, 0 };

	return temp;
}

Point getZeroPoint2() {
	return Point { 0, 0 };
}

Point getZeroPoint3() {
	return { 0, 0 };
}
