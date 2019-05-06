#include <iostream>
#include <iterator>
#include <optional>
#include <string>
#include <unordered_set>

std::optional<char> GetFirstRecurringCharacter(const std::string& string) noexcept
{
	std::unordered_set<char> letterCounts;

	for (const char letter : string)
	{
		if (letterCounts.find(letter) == std::cend(letterCounts))
		{
			letterCounts.insert(letter);
		}
		else
		{
			return letter;
		}
	}

	return std::nullopt;
}

int main(int argc, char* argv[])
{
	std::cout << GetFirstRecurringCharacter("acbbac").value() << "\n";
	std::cout << GetFirstRecurringCharacter("abcdef").value_or('*') << "\n";

	std::cin.get();

	return 0;
}