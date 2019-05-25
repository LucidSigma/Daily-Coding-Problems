#include <iostream>
#include <random>
#include <utility>

inline unsigned int RollDice() noexcept
{
	static std::random_device randomSeed{ };
	static std::mt19937 randomEngine{ randomSeed() };
	const static std::uniform_int_distribution<unsigned int> randomRange{ 1, 6 };

	return randomRange(randomEngine);
}

unsigned int PlayDiceGame(const std::pair<unsigned int, unsigned int>& stoppingPair) noexcept
{
	unsigned int previousRoll = RollDice();
	unsigned int counter = 1;

	bool stoppingPairMatched = false;

	while (!stoppingPairMatched)
	{
		const unsigned int currentRoll = RollDice();
		++counter;

		if (std::make_pair(previousRoll, currentRoll) == stoppingPair)
		{
			stoppingPairMatched = true;
		}

		previousRoll = currentRoll;
	}

	return counter;
}

int main(int argc, char* argv[])
{
	unsigned int gameOne = 0;
	unsigned int gameTwo = 0;

	for (unsigned int i = 0; i < 10'000; ++i)
	{
		gameOne += PlayDiceGame({ 5, 6 });
		gameTwo += PlayDiceGame({ 5, 5 });
	}

	const float gameOneAverage = gameOne / 10'000.0f;
	const float gameTwoAverage = gameTwo / 10'000.0f;

	std::cout << "Game one average: " << gameOneAverage << "\n";
	std::cout << "Game two average: " << gameTwoAverage << "\n";

	// The is no difference between either game, since each roll is independent of each other

	std::cin.get();

	return 0;
}