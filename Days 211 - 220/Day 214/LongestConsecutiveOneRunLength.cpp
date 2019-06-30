#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

std::string ConvertDecimalToBinary(unsigned int number) noexcept
{
	std::string binaryNumber;

	while (number > 0)
	{
		binaryNumber += std::to_string(number % 2);
		number /= 2;
	}

	std::reverse(std::begin(binaryNumber), std::end(binaryNumber));

	return binaryNumber;
}

unsigned int LongestConsecutiveOneLength(const unsigned int number) noexcept
{
	const std::string binaryNumber = ConvertDecimalToBinary(number);
	unsigned int maxLength = 0;
	unsigned int currentLength = 0;

	for (const auto digit : binaryNumber)
	{
		if (digit == '0')
		{
			maxLength = std::max(currentLength, maxLength);
			currentLength = 0;
		}
		else
		{
			++currentLength;
		}
	}

	return std::max(currentLength, maxLength);
}

int main(int argc, char* argv[])
{
	std::cout << LongestConsecutiveOneLength(156) << "\n";

	std::cin.get();

	return 0;
}