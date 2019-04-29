#include <array>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

template <unsigned int Size>
int GetNumberWithProbabilities(const std::array<int, Size>& numbers, const std::array<float, Size>& probabilities)
{
	static std::random_device randomSeed;
	static std::mt19937 randomEngine(randomSeed());
	static std::uniform_real_distribution<float> randomRange(0.0f, 1.0f);

	float randomNumber = randomRange(randomEngine);
	float progressiveProbability = 0.0f;

	for (unsigned int i = 0; i < Size; i++)
	{
		progressiveProbability += probabilities[i];

		if (randomNumber <= progressiveProbability)
		{
			return numbers[i];
		}
	}

	throw std::invalid_argument("Probabilities do not sum to 1.0");
}

int main(int argc, char* argv[])
{
	std::array<std::string, 4> histogram;
	std::array<int, 4> numbers { 1, 2, 3, 4 };
	std::array<float, 4> probabilities { 0.1f, 0.5f, 0.2f, 0.2f };

	for (unsigned int i = 0; i < 100; i++)
	{
		histogram[GetNumberWithProbabilities(numbers, probabilities) - 1] += '*';
	}

	for (unsigned int i = 0; i < 4; i++)
	{
		std::cout << numbers[i] << ": " << histogram[i] << "\n";
	}

	std::cin.get();

	return 0;
}