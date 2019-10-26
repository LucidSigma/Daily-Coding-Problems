#include <cstdlib>
#include <iostream>

unsigned int SatisfactoryIntegerPairCount(const unsigned int m, const unsigned int n)
{
	unsigned int satisfactoryPairCount = 0;

	for (unsigned int a = 0; a < (m / 2) + 1; ++a)
	{
		const unsigned int b = m - a;

		if ((a ^ b) == n)
		{
			++satisfactoryPairCount;
		}
	}

	return satisfactoryPairCount;
}

int main(const int argc, const char* const argv[])
{
	std::cout << SatisfactoryIntegerPairCount(64, 48) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}