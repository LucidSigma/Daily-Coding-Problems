#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

unsigned int GetLastSurvivor(const unsigned int n, const unsigned int k) noexcept
{
	unsigned int lastSurivor = 0;
	size_t currentExecutionIndex = 0;

	std::vector<unsigned int> prisoners(n);
	std::iota(std::begin(prisoners), std::end(prisoners), 1);

	while (!prisoners.empty())
	{
		currentExecutionIndex = (currentExecutionIndex + k - 1) % prisoners.size();
		lastSurivor = prisoners[currentExecutionIndex];
		
		std::vector<unsigned int> newPrisoners(std::cbegin(prisoners), std::cbegin(prisoners) + currentExecutionIndex);
		newPrisoners.insert(std::cend(newPrisoners), std::cbegin(prisoners) + currentExecutionIndex + 1, std::cend(prisoners));

		prisoners = newPrisoners;
	}

	return lastSurivor;
}

int main(int argc, char* argv[])
{
	std::cout << GetLastSurvivor(5, 2) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}
