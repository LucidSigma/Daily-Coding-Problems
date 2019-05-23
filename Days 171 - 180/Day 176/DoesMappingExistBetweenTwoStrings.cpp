#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <utility>

inline std::pair<std::string::const_iterator, std::string::const_iterator> cbegin(const std::pair<std::string, std::string>& stringPair) noexcept
{
	return { std::begin(stringPair.first), std::begin(stringPair.second) };
}

inline std::pair<std::string::const_iterator, std::string::const_iterator> cend(const std::pair<std::string, std::string>& stringPair) noexcept
{
	return { std::end(stringPair.first), std::end(stringPair.second) };
}

inline std::pair<std::string::const_iterator, std::string::const_iterator> operator ++(std::pair<std::string::const_iterator, std::string::const_iterator>& stringPair) noexcept
{
	return { ++stringPair.first, ++stringPair.second };
}

bool DoesMappingExist(const std::string& s1, const std::string& s2) noexcept
{
	if (s1.length() != s2.length())
	{
		return false;
	}

	std::unordered_map<char, char> letterMapping;
	const std::pair<std::string, std::string> stringPair{ s1, s2 };

	for (auto it = cbegin(stringPair); it != cend(stringPair); ++it)
	{
		const auto [letter1, letter2] = std::make_pair( *it.first, *it.second );

		if (letterMapping.find(letter1) == std::cend(letterMapping))
		{
			letterMapping[letter1] = letter2;
		}
		else if (letterMapping[letter1] != letter2)
		{
			return false;
		}
	}

	return true;
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << DoesMappingExist("abc", "bcd") << "\n";
	std::cout << DoesMappingExist("foo", "bar") << "\n";

	std::cin.get();

	return 0;
}