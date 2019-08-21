#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

std::vector<std::string> GetStepWords(const std::string& inputWord, const std::unordered_set<std::string>& dictionary)
{
	std::vector<std::string> stepWords;

	for (const auto& word : dictionary)
	{
		size_t letterRemovalCount = 0;
		std::string decayingWord = word;

		for (const auto letter : inputWord)
		{
			if (const auto letterPosition = decayingWord.find(letter);
				letterPosition != std::string::npos)
			{
				decayingWord.erase(letterPosition, 1);
				++letterRemovalCount;
			}
		}

		if (letterRemovalCount == inputWord.length() && decayingWord.length() == 1)
		{
			stepWords.push_back(word);
		}
	}

	return stepWords;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << GetStepWords("APPLE", { "APPLY", "APPEAL", "APPELS", "STRIKE" }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}