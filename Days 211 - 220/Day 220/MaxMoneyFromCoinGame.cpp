#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

unsigned int GetMaxAmountOfMoneyHelper(const std::vector<unsigned int>& coins, const unsigned int currentAmount, const bool playerTurn) noexcept
{
	if (coins.empty())
	{
		return currentAmount;
	}

	if (playerTurn)
	{
		const unsigned int firstOutcome = GetMaxAmountOfMoneyHelper(std::vector<unsigned int>(std::cbegin(coins) + 1, std::cend(coins)), currentAmount + coins[0], false);
		const unsigned int lastOutcome = GetMaxAmountOfMoneyHelper(std::vector<unsigned int>(std::cbegin(coins), std::cend(coins) - 1), currentAmount + coins.back(), false);

		return std::max(firstOutcome, lastOutcome);
	}
	else
	{
		const unsigned int firstCoin = coins[0];
		const unsigned int lastCoin = coins.back();

		const std::vector<unsigned int> optimalCoinTaken = coins[0] > coins.back()
														   ? std::vector<unsigned int>(std::cbegin(coins) + 1, std::cend(coins))
														   : std::vector<unsigned int>(std::cbegin(coins), std::cend(coins) - 1);

		return GetMaxAmountOfMoneyHelper(optimalCoinTaken, currentAmount, true);
	}
}

unsigned int GetMaxAmountOfMoney(const unsigned int coinCount) noexcept
{
	std::vector<unsigned int> coins(coinCount);
	std::iota(std::begin(coins), std::end(coins), 1);

	return GetMaxAmountOfMoneyHelper(coins, 0, true);
}

int main(int argc, char* argv[])
{
	std::cout << GetMaxAmountOfMoney(10) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}