#include <functional>
#include <iostream>

using PairFunction = std::function<int(int, int)>;
using ReturnedFunction = std::function<int(PairFunction)>;

ReturnedFunction cons(int a, int b)
{
	auto pair = [a, b](PairFunction f) -> int
	{
		return f(a, b);
	};

	return pair;
}

int car(ReturnedFunction pair)
{
	auto firstVar = [](int a, int b) -> int
	{
		return a;
	};

	return pair(firstVar);
}

int cdr(ReturnedFunction pair)
{
	auto secondVar = [](int a, int b) -> int
	{
		return b;
	};

	return pair(secondVar);
}

int main(int argc, char* argv[])
{
	std::cout << car(cons(3, 4)) << "\n";
	std::cout << cdr(cons(3, 4)) << "\n";

	std::cin.get();

	return 0;
}