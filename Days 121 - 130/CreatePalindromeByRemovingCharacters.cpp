#include <iostream>
#include <string>

bool IsPalindrome(const std::string& string) noexcept
{
	if (string.empty())
	{
		return false;
	}

	for (unsigned int i = 0; i < string.length() / 2; i++)
	{
		if (string[i] != string[string.length() - i - 1])
		{
			return false;
		}
	}

	return true;
}

bool CanMakePalindromeWithRemovals(const std::string& string, const unsigned int k) noexcept
{
	if (IsPalindrome(string))
	{
		return true;
	}

	if (k == 0)
	{
		return false;
	}

	for (unsigned int i = 0; i < string.length(); i++)
	{
		std::string shortenedString = string;
		shortenedString.erase(i);

		if (CanMakePalindromeWithRemovals(shortenedString, k - 1))
		{
			return true;
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << CanMakePalindromeWithRemovals("waterrfetawx", 2) << "\n";

	std::cin.get();

	return 0;
}