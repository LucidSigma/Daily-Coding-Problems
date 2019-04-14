#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

class BitArray
{
private:
	static constexpr unsigned int BitsPerChar = sizeof(char) * 8u;

	std::vector<char> data;
	unsigned int size = 0;

public:
	explicit BitArray(const char size) noexcept
		: size(size), data(static_cast<unsigned int>(std::ceil(static_cast<float>(size) / static_cast<float>(BitsPerChar))))
	{
		std::fill(std::begin(data), std::end(data), 0);
	}

	void Set(const unsigned int i, const bool value)
	{
		if (i > size)
		{
			throw std::invalid_argument("Index out of range.");
		}

		const unsigned int charIndex = i / BitsPerChar;
		const unsigned int offset = i - (charIndex * BitsPerChar);
		const unsigned char mask = (1 & static_cast<char>(value)) << offset;

		data[charIndex] |= mask;
	}

	bool Get(const unsigned int i) const
	{
		if (i > size)
		{
			throw std::invalid_argument("Index out of range.");
		}

		const unsigned int charIndex = i / BitsPerChar;
		const unsigned int offset = i - (charIndex * BitsPerChar);
		const unsigned char mask = 1 << offset;

		return data[charIndex] & mask;
	}

	inline unsigned int Size() const noexcept { return size; }
};

void PrintBitArray(const BitArray& bitArray) noexcept
{
	for (unsigned int i = 0; i < bitArray.Size(); i++)
	{
		std::cout << bitArray.Get(i) << "\n";
	}
}

int main(int argc, char* argv[])
{
	BitArray bitArray(10);

	bitArray.Set(1, true);
	bitArray.Set(2, true);
	bitArray.Set(4, true);
	bitArray.Set(6, true);
	bitArray.Set(8, true);
	bitArray.Set(9, true);

	PrintBitArray(bitArray);

	std::cin.get();

	return 0;
}