#include <iostream>
#include <random>

int SelectRandomFromStream(int currentNumber, bool resetStream = false)
{
	static int randomStreamNumber = 0;
	static int count = 0;

	if (resetStream)
	{
		randomStreamNumber = 0;
		count = 0;
	}

	count++;

	if (count == 1)
	{
		randomStreamNumber = currentNumber;
	}
	else
	{
		static std::random_device randomSeed;
		static std::mt19937 randomEngine(randomSeed());
		std::uniform_int_distribution<int> randomGenerator(0, count);

		int randomNumber = randomGenerator(randomEngine);

		if (randomNumber == count - 1)
		{
			randomStreamNumber = currentNumber;
		}
	}

	return randomStreamNumber;
}

int main(int argc, char* argv[])
{
	int randomNumber = 0;

	do
	{
		std::cout << "Enter a number (or \"quit\" to stop): ";

		int currentNumber;
		std::cin >> currentNumber;

		if (!std::cin.fail())
		{
			randomNumber = SelectRandomFromStream(currentNumber);
		}
	}
	while (!std::cin.fail());

	std::cin.clear();
	std::cin.ignore(10000, '\n');

	std::cout << "Random number: " << randomNumber << std::endl;

	std::cin.get();

	return 0;
}