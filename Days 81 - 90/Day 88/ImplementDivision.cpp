#include <iostream>
#include <stdexcept>

unsigned int Divide(unsigned int a, unsigned int b)
{
	if (b == 0)
	{
		throw std::runtime_error("Cannot divide by zero.");
	}

	unsigned int quotient = 0;

	while (a >= b)
	{
		a -= b;
		quotient++;
	}

	return quotient;
}

int main(int argc, char* argv[])
{
	std::cout << "12 / 6 = " << Divide(12, 6) << "\n";
	std::cout << "12 / 5 = " << Divide(12, 5) << "\n";
	std::cout << "360 / 7 = " << Divide(360, 7) << "\n";
	std::cout << "1 / 10 = " << Divide(1, 10) << "\n";

	try
	{
		std::cout << "4 / 0 = " << Divide(4, 0) << "\n";
	}
	catch (const std::runtime_error& error)
	{
		std::cout << error.what() << "\n";
	}

	std::cin.get();

	return 0;
}