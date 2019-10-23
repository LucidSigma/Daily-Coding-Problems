#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using Person = std::string;
using Couple = std::pair<Person, Person>;

std::vector<Couple> FindBestMatches(std::unordered_map<Person, std::vector<Person>> guyPreferences, std::unordered_map<Person, std::vector<Person>> galPreferences)
{
	if (guyPreferences.empty())
	{
		return { };
	}

	std::vector<Couple> bestMatches;
	std::unordered_set<Person> takenGuys;
	std::unordered_set<Person> takenGals;

	for (const auto& [guy, preferences] : guyPreferences)
	{
		const Person currentGal = preferences[0];
		const Person preferredGuy = galPreferences[currentGal][0];

		if (preferredGuy == guy)
		{
			bestMatches.push_back({ guy, currentGal });
			takenGuys.insert(guy);
			takenGals.insert(currentGal);
		}
	}

	if (bestMatches.empty())
	{
		for (const auto& [guy, preferences] : guyPreferences)
		{
			const Person currentGal = preferences[0];
			bestMatches.push_back({ guy, currentGal });
		}

		return bestMatches;
	}

	for (const auto& [guy, gal] : bestMatches)
	{
		guyPreferences.erase(guy);
		galPreferences.erase(gal);

		for (auto& [otherGuy, otherPreferences] : guyPreferences)
		{
			std::vector<Person> newPreferences;

			for (const auto& candidateGal : otherPreferences)
			{
				if (takenGals.find(candidateGal) == std::cend(takenGals))
				{
					newPreferences.push_back(candidateGal);
				}
			}

			otherPreferences = newPreferences;
		}

		for (auto& [otherGal, otherPreferences] : galPreferences)
		{
			std::vector<Person> newPreferences;

			for (const auto& candidateGuy : otherPreferences)
			{
				if (takenGuys.find(candidateGuy) == std::cend(takenGuys))
				{
					newPreferences.push_back(candidateGuy);
				}
			}

			otherPreferences = newPreferences;
		}
	}

	const auto successiveBestMatches = FindBestMatches(guyPreferences, galPreferences);
	bestMatches.insert(std::cend(bestMatches), std::cbegin(successiveBestMatches), std::cend(successiveBestMatches));

	return bestMatches;
}

template <typename T, typename U>
inline std::ostream& operator <<(std::ostream& outputStream, const std::pair<T, U>& pair)
{
	outputStream << "( " << pair.first << ", " << pair.second << " )";

	return outputStream;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << "\n";
	}

	return outputStream;
}

int main(const int argc, const char* const argv[])
{
	const std::unordered_map<Person, std::vector<Person>> guyPreferences
	{
		{ "andrew", { "caroline", "abigail", "betty" } },
		{ "bill", { "caroline", "betty", "abigail" } },
		{ "chester", { "betty", "caroline", "abigail" } }
	};

	const std::unordered_map<Person, std::vector<Person>> galPreferences
	{
		{ "abigail", { "andrew", "bill", "chester" } },
		{ "betty", { "bill", "andrew", "chester" } },
		{ "caroline", { "bill", "chester", "andrew" } }
	};

	std::cout << FindBestMatches(guyPreferences, galPreferences) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}