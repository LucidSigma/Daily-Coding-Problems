#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

[[nodiscard]]
unsigned int GetMinFlipCount(const std::string& letters)
{
	const size_t lastXIndex = letters.find_last_of('x');
	const size_t firstYIndex = letters.find_first_of('y');

	unsigned int xCount = 0;
	unsigned int yCount = 0;

	for (size_t i = 0; i < lastXIndex; ++i)
	{
		if (letters[i] == 'y')
		{
			++yCount;
		}
	}

	for (size_t i = firstYIndex + 1; i < letters.length(); ++i)
	{
		if (letters[i] == 'x')
		{
			++xCount;
		}
	}

	return std::min(xCount, yCount);
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetMinFlipCount("xyxxxyxyy") << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}