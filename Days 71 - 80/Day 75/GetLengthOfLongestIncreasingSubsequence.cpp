#include <array>
#include <iostream>
#include <unordered_map>

template <unsigned int Size>
unsigned int GetLongestIncreasingSubsequenceLengthHelper(const std::array<int, Size>& array, unsigned int startIndex) noexcept
{
	static std::unordered_map<unsigned int, unsigned int> numberCache;

	if (startIndex == Size)
	{
		return 0;
	}

	const int currentNumber = array[startIndex];
	unsigned int maxIncrement = 1;

	for (unsigned int i = startIndex + 1; i < Size; i++)
	{
		unsigned int count;

		if (array[i] >= currentNumber)
		{
			if (numberCache.find(i) != numberCache.end())
			{
				count = numberCache[i];
			}
			else
			{
				count = GetLongestIncreasingSubsequenceLengthHelper(array, i) + 1;
				numberCache[i] = count;
			}

			if (count > maxIncrement)
			{
				maxIncrement = count;
			}
		}
	}

	return maxIncrement;
}

template <unsigned int Size>
inline unsigned int GetLongestIncreasingSubsequenceLength(const std::array<int, Size>& array) noexcept
{
	return GetLongestIncreasingSubsequenceLengthHelper(array, 0);
}

int main(int argc, char* argv[])
{
	std::cout << GetLongestIncreasingSubsequenceLength<16>({ 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 }) << "\n";

	std::cin.get();

	return 0;
}