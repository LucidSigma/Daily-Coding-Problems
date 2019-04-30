#include <algorithm>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> SplitString(const std::string& text, const char delimiter = ' ')
{
	std::string currentToken;
	std::stringstream reader(text);
	std::vector<std::string> tokens;

	while (std::getline(reader, currentToken, delimiter))
	{
		tokens.push_back(currentToken);
	}

	return tokens;
}

std::optional<unsigned int> SmallestDistanceBetweenWords(const std::string& text, const std::string& wordA, const std::string& wordB) noexcept
{
	std::optional<unsigned int> distance { };
	const std::vector<std::string> words = SplitString(text);

	unsigned int previousValidIndex = 0;
	std::string previousValidWord;

	for (unsigned int i = 0; i < words.size(); ++i)
	{
		if (words[i] == wordA || words[i] == wordB)
		{
			if ((words[i] == wordA && previousValidWord == wordB) || (words[i] == wordB && previousValidWord == wordA))
			{
				distance = std::min(distance.value_or(std::numeric_limits<unsigned int>::max()), i - previousValidIndex - 1);
			}

			previousValidIndex = i;
			previousValidWord = words[i];
		}
	}

	return distance;
}

int main(int argc, char* argv[])
{
	std::cout << SmallestDistanceBetweenWords("dog cat hello cat dog dog hello cat world", "hello", "world").value() << "\n";
	std::cout << SmallestDistanceBetweenWords("dog cat hello world cat dog dog hello cat world", "hello", "world").value() << "\n";
	std::cout << SmallestDistanceBetweenWords("dog cat hello cat dog dog hello cat world", "hello", "none").value_or(-1) << "\n";
	
	std::cin.get();

	return 0;
}