#include <algorithm>
#include <iostream>
#include <string>

inline bool IsPalindrome(const std::string& string)
{
	std::string reversedString = string;
	std::reverse(reversedString.begin(), reversedString.end());

	return string == reversedString;
}

std::string GetMinimumPalindrome(const std::string& string)
{
	if (IsPalindrome(string))
	{
		return string;
	}

	if (string[0] == string[string.length() - 1])
	{
		return string[0] + GetMinimumPalindrome(string.substr(1, string.length() - 2)) + string[string.length() - 1];
	}
	else
	{
		std::string firstPalindrome = string[0] + GetMinimumPalindrome(string.substr(1)) + string[0];
		std::string secondPalindrome = string[string.length() - 1] + GetMinimumPalindrome(string.substr(0, string.length() - 1)) + string[string.length() - 1];

		if (firstPalindrome.length() > secondPalindrome.length())
		{
			return secondPalindrome;
		}
		else if (firstPalindrome.length() < secondPalindrome.length())
		{
			return firstPalindrome;
		}
		else
		{
			return (firstPalindrome < secondPalindrome) ? firstPalindrome : secondPalindrome;
		}
	}
}

int main(int argc, const char* argv[])
{
	std::cout << GetMinimumPalindrome("racecar") << "\n";
	std::cout << GetMinimumPalindrome("race") << "\n";
	std::cout << GetMinimumPalindrome("google") << "\n";

	std::cin.get();

	return 0;
}