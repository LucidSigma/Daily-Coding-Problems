#include <cstdlib>
#include <iostream>

unsigned int GetTotalSetBits(const unsigned int n)
{
	if (n == 0)
	{
		return 0;
	}

	unsigned int currentMagnitude = 0;
	unsigned int currentPowerOfTwo = 1;

	while (currentPowerOfTwo - 1 <= n)
	{
		currentPowerOfTwo <<= 1;
		++currentMagnitude;
	}

	currentPowerOfTwo >>= 1;
	--currentMagnitude;

	const unsigned int remainder = n - currentPowerOfTwo + 1;
	unsigned int setBitCount = (currentMagnitude * currentPowerOfTwo) >> 1;
	setBitCount += GetTotalSetBits(remainder);

	return setBitCount;
}

int main(const int argc, const char* const argv[])
{
	for (unsigned int i = 1; i <= 16; ++i)
	{
		std::cout << GetTotalSetBits(i) << "\n";
	}

	std::cin.get();

	return EXIT_SUCCESS;
}