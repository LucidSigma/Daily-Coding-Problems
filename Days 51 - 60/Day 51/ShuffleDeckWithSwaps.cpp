#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <utility>
#include <vector>

struct Card
{
	static constexpr unsigned int CARDS_PER_DECK = 52;

	std::string value;
	std::string suit;

	explicit Card(std::string value, std::string suit)
		: value(value), suit(suit)
	{ }
};

unsigned int RandomNumber(unsigned int max)
{
	static std::random_device randomSeed;
	static std::mt19937 randomEngine(randomSeed());
	std::uniform_int_distribution<int> randomRange(1, max);

	return randomRange(randomEngine);
}

void ShuffleDeck(std::vector<Card>& deck) noexcept
{
	for (unsigned int i = 0; i < deck.size(); i++)
	{
		unsigned int swapIndex = RandomNumber(Card::CARDS_PER_DECK) - 1;
		std::swap(deck[i], deck[swapIndex]);
	}
}

std::vector<Card> CreateDeck()
{
	static const std::string values[] { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	static const std::string suits[] { "S", "H", "C", "D" };

	std::vector<Card> deck;
	deck.reserve(Card::CARDS_PER_DECK);

	for (const auto& suit : suits)
	{
		for (const auto& value : values)
		{
			deck.emplace_back(value, suit);
		}
	}

	return deck;
}

void PrintDeck(const std::vector<Card>& deck)
{
	for (unsigned int i = 0; i < deck.size(); i++)
	{
		std::cout << deck[i].value << deck[i].suit;

		if (i < deck.size() - 1)
		{
			std::cout << ",";
		}

		std::cout << " ";
	}

	std::cout << "\n";
}

int main(int argc, const char* argv[])
{
	std::vector<Card> deck = CreateDeck();
	PrintDeck(deck);

	std::cout << "\n";

	ShuffleDeck(deck);
	PrintDeck(deck);

	std::cin.get();

	return 0;
}