#include <cmath>
#include <iostream>
#include <stdexcept>

float Pow(int x, int y)
{
	if (x == 0 && y == 0)
	{
		throw std::invalid_argument("Undefined operation.");
	}

	if (y == 0)
	{
		return 1;
	}

	unsigned int positiveY = std::abs(y);
	unsigned int currentPower = 1;
	unsigned int previousPower = 0;

	float previousResult = 0.0f;
	float result = x;

	while (currentPower <= positiveY)
	{
		previousResult = result;
		previousPower = currentPower;
		result *= result;
		currentPower <<= 1;
	}

	previousResult *= Pow(x, positiveY - previousPower);

	return y != positiveY ? 1.0f / previousResult : previousResult;
}

int main(int argc, char* argv[])
{
	std::cout << Pow(2, 10) << "\n";
	std::cout << Pow(2, -10) << "\n";
	std::cout << Pow(10, 3) << "\n";
	std::cout << Pow(10, -3) << "\n";
	std::cout << Pow(5, 0) << "\n";

	try
	{
		std::cout << Pow(0, 0) << "\n";
	}
	catch (const std::invalid_argument&)
	{
		std::cout << "0 ^ 0 is undefined.\n";
	}

	std::cin.get();

	return 0;
}
