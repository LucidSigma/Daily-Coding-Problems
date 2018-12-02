/*
	This type of problem is not well suited for C++ due to how its lambdas work
	I had to make a workaround using a functor class
*/

#include <iostream>

class HelperFunctor
{
private:
	int a;
	int b;

public:
	HelperFunctor(int a, int b)
		: a(a), b(b)
	{ }

	int operator ()(int (* f)(int, int))
	{
		return f(a, b);
	}
};

HelperFunctor cons(int a, int b)
{
	return HelperFunctor(a, b);
}

int car(HelperFunctor pair)
{
	auto first_var = [](int a, int b) -> int
	{
		return a;
	};

	return pair(first_var);
}

int cdr(HelperFunctor pair)
{
	auto second_var = [](int a, int b) -> int
	{
		return b;
	};

	return pair(second_var);
}

int main(int argc, char* argv[])
{
	std::cout << car(cons(3, 4)) << std::endl;
	std::cout << cdr(cons(3, 4)) << std::endl;

	std::cin.get();
	
	return 0;
}