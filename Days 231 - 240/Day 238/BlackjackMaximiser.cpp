#include <cstdlib>
#include <iostream>
#include <iterator>
#include <random>
#include <unordered_map>

std::unordered_map<unsigned int, float> CreateCardCounts()
{
	std::unordered_map<unsigned int, float> cardValueCounts;

	for (unsigned int i = 1; i <= 10; ++i)
	{
		if (cardValueCounts.find(i) == std::cend(cardValueCounts))
		{
			cardValueCounts[i] = 0.0f;
		}

		if (i == 10)
		{
			cardValueCounts[i] += 4.0f;
		}
		else
		{
			++cardValueCounts[i];
		}
	}

	float totalCardValue = 0.0f;

	for (const auto [_, value] : cardValueCounts)
	{
		totalCardValue += value;
	}

	float previousValue = 0.0f;

	for (auto& [_, value] : cardValueCounts)
	{
		value = previousValue + (value / totalCardValue);
		previousValue = value;
	}

	return cardValueCounts;
}

unsigned int DrawCard(const std::unordered_map<unsigned int, float>& cards)
{
	static std::random_device randomSeed;
	static std::mt19937 randomEngine(randomSeed());
	static std::uniform_real_distribution<float> randomRange(0.0f, 1.0f);

	const float randomValue = randomRange(randomEngine);
	float lowerLimit = 0.0f;
	float upperLimit = 0.0f;

	for (const auto [card, value] : cards)
	{
		upperLimit = value;

		if (randomValue >= lowerLimit && randomValue <= upperLimit)
		{
			return card;
		}

		lowerLimit = upperLimit;
	}
}

bool PlayBlackjackTurn(unsigned int& playerScore, unsigned int& dealerScore, const bool isDealersTurn, const std::unordered_map<unsigned int, float>& cards)
{
	static constexpr unsigned int WinThreshold = 21u;

	if (static constexpr unsigned int DealerThreshold = 16u;
		isDealersTurn && dealerScore < DealerThreshold)
	{
		const unsigned int nextCard = DrawCard(cards);
		dealerScore += nextCard;

		return dealerScore > WinThreshold;
	}

	if (playerScore < WinThreshold)
	{
		const unsigned int nextCard = DrawCard(cards);

		if (playerScore + nextCard <= WinThreshold)
		{
			playerScore += nextCard;
		}
	}

	return false;
}

void PlayBlackjackGame()
{
	unsigned int playerScore = 0;
	unsigned int dealerScore = 0;

	bool hasWonGame = false;
	bool isDealersTurn = false;

	const auto cards = CreateCardCounts();

	while (!hasWonGame)
	{
		hasWonGame = PlayBlackjackTurn(playerScore, dealerScore, isDealersTurn, cards);
		isDealersTurn = !isDealersTurn;
	}

	std::cout << "Player's score: " << playerScore << "\nDealer's score: " << dealerScore << "\n";
}

int main(int argc, char* argv[])
{
	PlayBlackjackGame();

	std::cin.get();

	return EXIT_SUCCESS;
}