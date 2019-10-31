#include <bitset>
#include <cstdlib>
#include <iostream>

inline unsigned int GetSetBits(const unsigned int number) noexcept
{
	return std::bitset<sizeof(unsigned int) * 8u>(number).count();
}

unsigned int GetNextNumberWithSameSetBitCount(const unsigned int number)
{
	const unsigned int initialSetBitCount = GetSetBits(number);
	unsigned int nextNumberDifference = 1;

	while (GetSetBits(number + nextNumberDifference) != initialSetBitCount)
	{
		++nextNumberDifference;
	}

	return number + nextNumberDifference;
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetNextNumberWithSameSetBitCount(6) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}