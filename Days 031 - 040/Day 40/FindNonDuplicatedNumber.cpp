#include <array>
#include <iostream>

template <unsigned int Size>
int GetNonDuplicatedNumber(const std::array<int, Size>& numbers)
{
	int uniqueNumber = 0;

	static constexpr unsigned int BITS_PER_INTEGER = sizeof(int) * 8;

	for (unsigned int i = 0; i < BITS_PER_INTEGER; i++)
	{
		int bitSums = 0;
		int currentBit = 1 << i;

		for (int number : numbers)
		{
			if (number & currentBit)
			{
				bitSums++;
			}
		}

		if (constexpr unsigned int NON_DUPLICATE_COUNT = 3; (bitSums % NON_DUPLICATE_COUNT) != 0)
		{
			uniqueNumber |= currentBit;
		}
	}

	return uniqueNumber;
}

int main(int argc, const char* argv[])
{
	std::cout << GetNonDuplicatedNumber<7>({ 6, 1, 3, 3, 3, 6, 6 }) << "\n";
	std::cout << GetNonDuplicatedNumber<4>({ 13, 19, 13, 13 }) << "\n";

	std::cin.get();

	return 0;
}