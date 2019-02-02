#include <iostream>
#include <string>
#include <random>
#include <vector>

unsigned int TossBiased()
{
	static std::random_device randomSeed;
	static std::mt19937 randomEngine(randomSeed());
	static std::uniform_int_distribution<unsigned int> randomRange(0, 10);

	unsigned int result = randomRange(randomEngine);

	return result < 7 ? 1 : 0;
}

unsigned int TossUnbiased()
{
	static constexpr unsigned int Iterations = 10'000u;
	std::vector<unsigned int> coinTosses { 0, 0 };

	for (unsigned int i = 0; i < Iterations; i++)
	{
		unsigned int currentFlip = TossBiased();
		currentFlip = i % 2 == 0 ? !currentFlip : currentFlip;
		coinTosses[currentFlip]++;
	}

	return coinTosses[0] < coinTosses[1] ? 1 : 0;
}

int main(int argc, char* argv[])
{
	static constexpr unsigned int TestCount = 100u;
	std::string histogram[] { "", "" };

	for (unsigned int i = 0; i < TestCount; i++)
	{
		unsigned int flip = TossUnbiased();
		histogram[flip] += '*';
	}

	for (unsigned int i = 0; i < 2; i++)
	{
		std::cout << i << " results: " << histogram[i] << "\n";
	}

	std::cin.get();

	return 0;
}