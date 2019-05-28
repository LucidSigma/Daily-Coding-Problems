#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

bool IsPalindrome(const std::string& string) noexcept
{
	std::string reversedString = string;
	std::reverse(std::begin(reversedString), std::end(reversedString));
	
	return string == reversedString;
}

std::vector<std::string> GetPalindromicSubstrings(const std::string& string) noexcept
{
	std::vector<std::string> palindromes;
	std::string shrinkingString = string;
	unsigned int currentSize = string.size();

	while (!shrinkingString.empty())
	{
		std::string currentSubstring = shrinkingString.substr(0, currentSize);

		if (IsPalindrome(currentSubstring))
		{
			palindromes.push_back(currentSubstring);
			shrinkingString = shrinkingString.substr(currentSize);
			currentSize = shrinkingString.size();
		}
		else
		{
			--currentSize;
		}		
	}

	return palindromes;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values) noexcept
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << GetPalindromicSubstrings("racecarannakayak") << "\n";
	std::cout << GetPalindromicSubstrings("abc") << "\n";

	std::cin.get();

	return 0;
}