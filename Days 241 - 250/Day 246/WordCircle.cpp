#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

bool CanCreateWordCircleHelper(std::vector<std::string> words, std::vector<std::string> currentChain)
{
	if (words.empty())
	{
		return currentChain.front().front() == currentChain.back().back();
	}

	const std::string& lastWord = !currentChain.empty() ? currentChain.back() : "";

	for (auto it = std::cbegin(words); it != std::cend(words); ++it)
	{
		const std::string& currentWord = *it;

		if (lastWord.empty() || currentWord.front() == lastWord.back())
		{
			currentChain.push_back(currentWord);
			words.erase(std::find(std::cbegin(words), std::cend(words), currentWord));

			if (CanCreateWordCircleHelper(words, currentChain))
			{
				return true;
			}
		}
	}

	return false;
}

inline bool CanCreateWordCircle(const std::vector<std::string>& words)
{
	return CanCreateWordCircleHelper(words, { });
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << CanCreateWordCircle({ "chair", "height", "racquet", "touch", "tunic" }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}