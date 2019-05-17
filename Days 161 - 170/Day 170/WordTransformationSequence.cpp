#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <unordered_set>
#include <vector>

std::vector<std::string> GetTransformationSequenceHelper(const std::string& start, const std::string& end, const std::unordered_set<std::string>& dictionary, const std::unordered_set<std::string>& usedWords, const std::vector<std::string>& sequence) noexcept
{
	if (start == end)
	{
		return sequence;
	}

	std::vector<std::string> validSuccessorWords;

	for (unsigned int i = 0; i < start.size(); ++i)
	{
		for (char letter = 'a'; letter <= 'z'; ++letter)
		{
			const std::string possibleValidWord = start.substr(0, i) + letter + start.substr(i + 1);

			if (dictionary.find(possibleValidWord) != std::cend(dictionary) && usedWords.find(possibleValidWord) == std::cend(usedWords))
			{
				validSuccessorWords.push_back(possibleValidWord);
			}
		}
	}

	std::vector<std::string> shortestSequence;
	unsigned int minSequenceLength = std::numeric_limits<unsigned int>::max();

	for (const auto& validWord : validSuccessorWords)
	{
		auto candidateUsedWords = usedWords;
		candidateUsedWords.insert(validWord);

		auto candidateSequence = sequence;
		candidateSequence.push_back(validWord);

		const auto validSequence = GetTransformationSequenceHelper(validWord, end, dictionary, candidateUsedWords, candidateSequence);
		
		if (!validSequence.empty() && validSequence.size() < minSequenceLength)
		{
			minSequenceLength = validSequence.size();
			shortestSequence = validSequence;
		}
	}

	return shortestSequence;
}

inline std::vector<std::string> GetTransformationSequence(const std::string& start, const std::string& end, const std::unordered_set<std::string>& dictionary) noexcept
{
	return GetTransformationSequenceHelper(start, end, dictionary, { start }, { start });
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values) noexcept
{
	if (values.empty())
	{
		outputStream << "Vector is empty.";
	}
	else
	{
		for (const auto& value : values)
		{
			outputStream << value << " ";
		}
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << GetTransformationSequence("dog", "cat", { "dot", "dop", "dat", "cat" }) << "\n";
	std::cout << GetTransformationSequence("dog", "cat", { "dot", "tod", "dat", "dar" }) << "\n";

	std::cin.get();

	return 0;
}