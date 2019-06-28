#include <cmath>
#include <iostream>
#include <string>

std::string GetAlphabeticalEncoding(unsigned int column) noexcept
{
	static constexpr unsigned int AlphabetLength = 26u;

	unsigned int letterCount = 1;
	unsigned int minMagnitude = 1;
	unsigned int maxMagnitude = AlphabetLength;

	while (column > maxMagnitude)
	{
		++letterCount;
		minMagnitude = maxMagnitude;
		maxMagnitude += static_cast<unsigned int>(std::pow(AlphabetLength, letterCount));
	}

	std::string encoding;

	for (unsigned int i = 0; i < letterCount; ++i)
	{
		const unsigned int offsetSize = (maxMagnitude - minMagnitude + 1) / AlphabetLength;
		unsigned int currentLetter = 0;
		unsigned int previousOffset = minMagnitude;
		unsigned int currentOffset = minMagnitude + offsetSize;

		while (column >= currentOffset)
		{
			++currentLetter;
			previousOffset = currentOffset;
			currentOffset = previousOffset + offsetSize;
		}

		encoding += 'A' + currentLetter;
		column -= previousOffset;

		minMagnitude = previousOffset;
		maxMagnitude = currentOffset;
	}

	return encoding;
}

int main(int argc, char* argv[])
{
	std::cout << GetAlphabeticalEncoding(1) << "\n";
	std::cout << GetAlphabeticalEncoding(27) << "\n";

	std::cin.get();

	return 0;
}