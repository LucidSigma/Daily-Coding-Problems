#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

int GetApproximateMedian(const std::vector<int>& numbers)
{
	static std::random_device randomSeed;
	static std::mt19937 randomEngine(randomSeed());
	
	const std::uniform_int_distribution<size_t> randomRange(0, numbers.size() - 1);
	std::priority_queue<int> numberQueue;

	for (size_t i = 0; i < numbers.size() / 2; ++i)
	{
		const size_t randomIndex = randomRange(randomEngine);
		numberQueue.push(numbers[randomIndex]);
	}

	for (size_t i = 0; i < numberQueue.size() / 2; ++i)
	{
		numberQueue.pop();
	}

	return numberQueue.top();
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetApproximateMedian({ 1, 4, 8, 3, 6, 4, 0, 1, 3, 4, 6, 2, 8, 0, 5, 4, 3, 6, 7, 3, 8 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}