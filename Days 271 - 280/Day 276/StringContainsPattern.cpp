#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <variant>

std::variant<size_t, bool> ContainsPattern(const std::string& string, const std::string& pattern)
{
	if (string.empty() || pattern.empty() || pattern.length() > string.length())
	{
		return false;
	}

	for (size_t i = 0; i <= string.length() - pattern.length(); ++i)
	{
		if (string.substr(i, pattern.length()) == pattern)
		{
			return i;
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << std::get<size_t>(ContainsPattern("abcdefgh", "cde")) << "\n";
	std::cout << std::get<bool>(ContainsPattern("abcdefgh", "ghi")) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}