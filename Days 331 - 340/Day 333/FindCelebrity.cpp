#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

using Person = char;

static const std::unordered_map<Person, std::unordered_set<Person>> g_knows
{
	{ 'a', { 'b', 'd' } },
	{ 'b', { } },
	{ 'c', { 'a', 'b', 'd' } },
	{ 'd', { 'a', 'b' } }
};

inline bool Knows(const Person a, const Person b)
{
	return g_knows.at(a).find(b) != std::cend(g_knows.at(a));
}

Person FindCelebrity()
{
	std::unordered_set<Person> potentialCelebrities;

	for (const auto& personKnows : g_knows)
	{
		potentialCelebrities.insert(personKnows.first);
	}

	while (!potentialCelebrities.empty())
	{
		const Person currentPerson = *std::cbegin(potentialCelebrities);
		potentialCelebrities.erase(currentPerson);
		
		size_t personCount = potentialCelebrities.size();

		for (const Person otherPerson : potentialCelebrities)
		{
			if (!Knows(currentPerson, otherPerson))
			{
				--personCount;
			}
		}

		if (personCount == 0)
		{
			return currentPerson;
		}
	}

	throw std::invalid_argument("No celebrity in set.");
}

int main(const int argc, const char* const argv[])
{
	std::cout << FindCelebrity() << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}