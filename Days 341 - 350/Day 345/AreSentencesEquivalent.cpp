#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using SynonymPair = std::pair<std::string, std::string>;

namespace std
{
	template <>
	struct hash<SynonymPair>
	{
		inline size_t operator ()(const SynonymPair& synonymPair) const noexcept
		{
			return (std::hash<std::string>()(synonymPair.first) << 15) ^ std::hash<std::string>()(synonymPair.second);
		}
	};
}

std::vector<std::string> SplitString(const std::string& text, const char delimiter = ' ')
{
	std::string currentToken;
	std::istringstream reader(text);

	std::vector<std::string> tokens;

	while (std::getline(reader, currentToken, delimiter))
	{
		tokens.push_back(currentToken);
	}

	return tokens;
}

inline bool AreSynonyms(const std::string& firstWord, const std::string& secondWord, const std::unordered_set<SynonymPair>& synonyms)
{
	if (firstWord == secondWord)
	{
		return true;
	}

	const SynonymPair firstPair{ firstWord, secondWord };
	const SynonymPair secondPair{ secondWord, firstWord };

	return synonyms.find(firstPair) != std::cend(synonyms) || synonyms.find(secondPair) != std::cend(synonyms);
}

bool AreSentencesEquivalent(const std::string& firstSentence, const std::string& secondSentence, const std::unordered_set<SynonymPair>& synonyms)
{
	const auto firstSentenceWords = SplitString(firstSentence);
	const auto secondSentenceWords = SplitString(secondSentence);

	if (firstSentenceWords.size() != secondSentenceWords.size())
	{
		return false;
	}

	for (size_t i = 0; i < firstSentenceWords.size(); ++i)
	{
		if (!AreSynonyms(firstSentenceWords[i], secondSentenceWords[i], synonyms))
		{
			return false;
		}
	}

	return true;
}

int main(const int argc, const char* const argv[])
{
	const std::unordered_set<SynonymPair> synonyms
	{
		{ "big", "large" },
		{ "eat", "consume" }
	};

	std::cout << std::boolalpha;
	std::cout << AreSentencesEquivalent("He wants to eat food.", "He wants to consume food.", synonyms) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}