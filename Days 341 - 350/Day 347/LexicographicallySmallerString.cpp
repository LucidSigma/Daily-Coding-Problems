#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>

std::string ModifyStringToBecomeLexicographicallySmaller(const std::string& string, const size_t k)
{
	if (k > 1)
	{
		std::string newString = string;
		std::sort(std::begin(newString), std::end(newString));

		return newString;
	}

	const char smallestLetter = *std::min_element(std::cbegin(string), std::cend(string));
	const std::string conjoinedString = string + string;

	for (size_t i = 0; i < conjoinedString.size(); ++i)
	{
		if (conjoinedString[i] == smallestLetter)
		{
			return std::string(std::cbegin(conjoinedString) + i, std::cbegin(conjoinedString) + i + string.size());
		}
	}

	return string;
}

int main(const int argc, const char* const argv[])
{
	std::cout << ModifyStringToBecomeLexicographicallySmaller("daily", 1) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}