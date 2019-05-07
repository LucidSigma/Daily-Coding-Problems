#include <bitset>
#include <iostream>

static constexpr unsigned int BitsPerByte = 8u;
static constexpr unsigned int BitsPerInt = sizeof(int) * BitsPerByte;

int ReverseBits(int number) noexcept
{
	int reversedNumber = 0;

	for (unsigned int i = 0; i < BitsPerInt; ++i)
	{
		reversedNumber |= (number & 1);
		number >>= 1;

		if (i != BitsPerInt - 1)
		{
			reversedNumber <<= 1;
		}
	}

	return reversedNumber;
}

int main(int argc, char* argv[])
{
	const int number = 0b1111'0000'1111'0000'1111'0000'1111'0000;

	std::cout << std::bitset<BitsPerInt>(number) << "\n";
	std::cout << std::bitset<BitsPerInt>(ReverseBits(number)) << "\n";

	std::cin.get();

	return 0;
}