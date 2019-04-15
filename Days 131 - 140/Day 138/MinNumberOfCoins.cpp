#include <array>
#include <iostream>

unsigned int GetMinNumberOfCoins(unsigned int total) noexcept
{
	static constexpr std::array<unsigned int, 4> Coins { 25, 10, 5, 1 };
	unsigned int coinCount = 0;
	unsigned int currentCoinIndex = 0;

	while (total > 0)
	{
		while (Coins[currentCoinIndex] > total)
		{
			currentCoinIndex++;
		}

		total -= Coins[currentCoinIndex];
		coinCount++;
	}

	return coinCount;
}

int main(int argc, char* argv[])
{
	std::cout << GetMinNumberOfCoins(16) << "\n";
	std::cout << GetMinNumberOfCoins(4) << "\n";
	std::cout << GetMinNumberOfCoins(41) << "\n";

	std::cin.get();

	return 0;
}