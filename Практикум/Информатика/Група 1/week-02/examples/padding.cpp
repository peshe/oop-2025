#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

struct A
{
	int c;
	char b;
	int a;
};

struct B
{
	int a;
	char b;
};

struct C
{
	A a;
	char b;
};

struct D
{
	int a;
	int b;
	char c;
	char d;
};

struct E
{
	int a;
	char c;
	int b;
	char d;
};

void printBytes(const unsigned char* obj, std::size_t size)
{
	std::ofstream old_state;
	old_state.copyfmt(std::cout); // save the state of std::cout before the call

	std::cout.setf(std::ios_base::hex, std::ios_base::basefield); // std::cout << std::hex; does the same
	std::cout.fill('0'); // std::cout << std::setfill('0'); does the same

	while(size--)
	{
		std::cout.width(2); // std::cout << std::setw(2); does the same
		std::cout << (int)*obj++ << ' ';
	}
	std::cout << '\n';

	std::cout.copyfmt(old_state); // restore the state of std::cout as it was before the call
}

bool equal(const D& a, const D& b)
{
	return a.a == b.a && a.b == b.b && a.c == b.c && a.d == b.d;
}

int main()
{
	D d1;
	D d2;
	d1.a = 0;
	d1.b = 0;
	d1.c = 0;
	d1.d = 0;

	d2.a = 0;
	d2.b = 0;
	d2.c = 0;
	d2.d = 0;

	std::cout << std::memcmp(&d1, &d2, sizeof(D)) << '\n';
	std::cout << equal(d1, d2) << '\n';

	printBytes((const unsigned char*)&d1, sizeof(d1));
	printBytes((const unsigned char*)&d2, sizeof(d2));

	//cout << sizeof(B) << endl;
	//B b[2];
	//b[0].a = -1;
	//b[0].b = '0';
	//b[1].a = 262;
	//b[1].b = 'A';

	return 0;
}
