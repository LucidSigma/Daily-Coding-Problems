#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>

std::optional<unsigned int> FindNextHigherPermutation(const unsigned int number) noexcept
{
	std::string numberString = std::to_string(number);
	int i = 0;

	for (i = numberString.length() - 1; i > 0; --i)
	{
		if (numberString[i] > numberString[i - 1])
		{
			break;
		}
	}

	if (i == 0)
	{
		return std::nullopt;
	}

	const char next = numberString[i - 1];
	std::size_t smallest = i;

	for (std::size_t j = i + 1; j < numberString.length(); ++j)
	{
		if (numberString[j] > next && numberString[j] < numberString[smallest])
		{
			smallest = j;
		}
	}

	std::swap(numberString[smallest], numberString[i - 1]);
	std::sort(std::begin(numberString) + i, std::end(numberString));

	std::istringstream converter{ numberString };
	unsigned int nextNumber = 0;

	converter >> nextNumber;

	return nextNumber;
}

int main(int argc, char* argv[])
{
	std::cout << FindNextHigherPermutation(48975).value_or(-1) << "\n";

	std::cin.get();

	return 0;
}