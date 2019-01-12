#include <iostream>
#include <random>
#include <string>

unsigned int Rand5()
{
	static constexpr unsigned int MAX = 5;

	static std::random_device randomSeed;
	static std::mt19937 randomEngine(randomSeed());
	static const std::uniform_int_distribution<unsigned int> randomRange(1, MAX);

	return randomRange(randomEngine);
}

unsigned int Rand7()
{
	static constexpr unsigned int MAX = 7;

	unsigned int total = 0;

	for (unsigned int i = 0; i < MAX; i++)
	{
		total += Rand5();
	}

	total %= MAX;

	return ++total;
}

int main(int argc, const char* argv[])
{
	std::string histogram[7];

	for (unsigned int i = 0; i < 250; i++)
	{
		histogram[Rand7() - 1] += '*';
	}

	for (unsigned int i = 0; i < 7; i++)
	{
		std::cout << i + 1 << ": " << histogram[i] << "\n";
	}

	std::cin.get();

	return 0;
}