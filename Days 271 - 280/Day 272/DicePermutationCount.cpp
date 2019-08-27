#include <cstdlib>
#include <iostream>

unsigned int GetDicePermutationCount(const unsigned int diceCount, const unsigned int facesPerDie, const unsigned int total)
{
	if (diceCount < 1 || total < 1)
	{
		return 0;
	}
	else if (diceCount == 1 && total <= facesPerDie)
	{
		return 1;
	}

	unsigned int permutationCount = 0;

	for (unsigned int i = 1; i <= facesPerDie; ++i)
	{
		permutationCount += GetDicePermutationCount(diceCount - 1, facesPerDie, total - i);
	}

	return permutationCount;
}

int main(int argc, char* argv[])
{
	std::cout << GetDicePermutationCount(3, 6, 7) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}