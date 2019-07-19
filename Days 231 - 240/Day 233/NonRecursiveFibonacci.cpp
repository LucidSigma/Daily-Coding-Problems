#include <cstdlib>
#include <iostream>

unsigned long long GetNthFibonacciNumber(const unsigned long long n) noexcept
{
	if (n == 0 || n == 1)
	{
		return n;
	}

	unsigned long long nthFibBackTwo = 0;
	unsigned long long nthFibBackOne = 1;
	unsigned long long nthFib = nthFibBackOne + nthFibBackTwo;

	for (unsigned long long i = 2; i < n; ++i)
	{
		nthFibBackTwo = nthFibBackOne;
		nthFibBackOne = nthFib;

		nthFib = nthFibBackOne + nthFibBackTwo;
	}

	return nthFib;
}

inline unsigned long long operator "" _fib(const unsigned long long n) noexcept
{
	return GetNthFibonacciNumber(n);
}

int main(int argc, char* argv[])
{
	std::cout << 5_fib << "\n";
	std::cout << 10_fib << "\n";
	std::cout << 15_fib << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}