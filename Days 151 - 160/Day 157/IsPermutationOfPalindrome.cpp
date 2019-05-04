#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>

bool IsPalindromePermutation(const std::string& word) noexcept
{
	std::unordered_set<char> usedChars;
	
	for (const char letter : word)
	{
		if (usedChars.find(letter) == std::cend(usedChars))
		{
			usedChars.insert(letter);
		}
		else
		{
			usedChars.erase(letter);
		}
	}

	return usedChars.size() <= 1;
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;

	std::cout << IsPalindromePermutation("carrace") << "\n";
	std::cout << IsPalindromePermutation("daily") << "\n";

	std::cin.get();

	return 0;
}