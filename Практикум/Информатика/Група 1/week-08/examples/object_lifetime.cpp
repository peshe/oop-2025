#include <iostream>

struct A
{
	int n;
	A(int n): n(n) { std::cout << "A(int): " << n << '\n'; }
	A(const A& a): n(10 * a.n) { std::cout << "A(const A&): " << n << '\n'; }
	~A() { std::cout << "~A(): " << n << '\n'; }
	void f() const { std::cout << "A::f(): " << n << '\n'; }
};

A a1(1);

A f(A a)
{
	A ret(-a.n);
	std::cout << "hello from f(): " << a.n << '\n';
	return ret;
}

int main()
{
	A *a2 = &a1;
	A a5(5);

	{
		A a3(3);
		std::cout << "----------------\n";
		std::cout << f(a3).n << '\n';
		std::cout << "----------------\n";
		std::cout << f(A(8)).n << '\n';
		std::cout << "----------------\n";
		A a4(4);
		a2 = new A(2); // assume it will not throw
		std::cout << "End of inner scope\n";
	}

	A(9).f();
	delete a2;
	a2 = new A(-2); // assume it will not throw
	std::cout << "End of main\n";
	return 0;
}

A a67[2]{6,7};
