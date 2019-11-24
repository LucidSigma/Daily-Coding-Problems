#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::vector<std::string> GetStrobogrammaticNumbers(const unsigned int digitCount)
{
	if (digitCount == 0)
	{
		return { "" };
	}
	else if (digitCount == 1)
	{
		return { "0", "1", "8" };
	}

	const auto successiveStrobogrammaticNumbers = GetStrobogrammaticNumbers(digitCount - 2);
	std::vector<std::string> strobogrammaticNumbers;

	for (const auto strobogrammaticNumber : successiveStrobogrammaticNumbers)
	{
		const std::vector<std::string> currentStrobogrammaticNumbers
		{
			"0" + strobogrammaticNumber + "0",
			"1" + strobogrammaticNumber + "1",
			"6" + strobogrammaticNumber + "9",
			"8" + strobogrammaticNumber + "8",
			"9" + strobogrammaticNumber + "6"
		};

		strobogrammaticNumbers.insert(std::cend(strobogrammaticNumbers), std::cbegin(currentStrobogrammaticNumbers), std::cend(currentStrobogrammaticNumbers));
	}

	return strobogrammaticNumbers;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetStrobogrammaticNumbers(5) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}