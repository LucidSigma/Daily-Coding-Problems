#include <cmath>
#include <cstdlib>
#include <iostream>

unsigned int GetFewestJumps(const int number)
{
	const unsigned int positiveNumber = std::abs(number);

	if (positiveNumber < 2)
	{
		return positiveNumber;
	}

	unsigned int currentNumber = 0;
	unsigned int targetNumber = 0;
	unsigned int jumpSize = 1;

	while (targetNumber <= positiveNumber)
	{
		currentNumber = targetNumber;
		targetNumber += jumpSize;

		++jumpSize;
	}

	jumpSize -= 2;

	return (2 * (positiveNumber - currentNumber)) + jumpSize;
}

int main(const int argc, const char* const argv[])
{
	for (int i = -10; i <= 10; ++i)
	{
		std::cout << GetFewestJumps(i) << "\n";
	}

	std::cin.get();

	return EXIT_SUCCESS;
}