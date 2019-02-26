#include <iostream>
#include <random>
#include <unordered_set>

unsigned int GetRandomNumberNotInList(const int n, const std::unordered_set<unsigned int>& excludedNumbers) noexcept
{
	static std::random_device randomSeeder;
	static std::mt19937 randomEngine(randomSeeder());

	std::uniform_int_distribution<unsigned int> randomRange(0, n - 1);
	unsigned int randomNumber;

	do
	{
		randomNumber = randomRange(randomEngine);
	}
	while (excludedNumbers.find(randomNumber) != excludedNumbers.end());

	return randomNumber;
}

int main(int argc, char* argv[])
{
	std::unordered_set<unsigned int> excludedNumbers { 3, 6, 9, 16, 11, 5 };

	for (unsigned int i = 0; i < 100; i++)
	{
		std::cout << GetRandomNumberNotInList(20, excludedNumbers) << " ";
	}

	std::cout << "\n";

	std::cin.get();

	return 0;
}