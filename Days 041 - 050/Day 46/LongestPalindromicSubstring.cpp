#include <algorithm>
#include <iostream>
#include <string>

bool IsPalindrome(const std::string& string)
{
	std::string reversedString = string;
	std::reverse_copy(string.begin(), string.end(), reversedString.begin());

	return string == reversedString;
}

std::string GetLongestPalindromicSubstring(const std::string& string)
{
	if (string.empty() || IsPalindrome(string))
	{
		return string;
	}

	std::string withoutFirst = GetLongestPalindromicSubstring(string.substr(1));
	std::string withoutLast = GetLongestPalindromicSubstring(string.substr(0, string.length() - 1));

	return withoutFirst.length() >= withoutLast.length() ? withoutFirst : withoutLast;
}

int main(int argc, const char* argv[])
{
	std::cout << GetLongestPalindromicSubstring("aabcdcb") << "\n";
	std::cout << GetLongestPalindromicSubstring("bananas") << "\n";

	std::cin.get();

	return 0;
}