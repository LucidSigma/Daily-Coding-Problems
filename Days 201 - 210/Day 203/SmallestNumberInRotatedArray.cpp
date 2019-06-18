#include <array>
#include <cstddef>
#include <iostream>

template <std::size_t Size>
int GetSmallestNumberInRotatedArrayHelper(const std::array<int, Size>& array, const std::size_t startIndex, const std::size_t endIndex) noexcept
{
	const std::size_t midpointIndex = startIndex + ((endIndex - startIndex) / 2);

	if (array[startIndex] <= array[midpointIndex])
	{
		return array[endIndex] < array[midpointIndex]
			   ? GetSmallestNumberInRotatedArrayHelper(array, midpointIndex + 1, endIndex)
			   : array[startIndex];
	}
	else
	{
		return array[endIndex] > array[midpointIndex]
			   ? GetSmallestNumberInRotatedArrayHelper(array, startIndex, endIndex)
			   : array[endIndex];
	}
}

template <std::size_t Size>
inline int GetSmallestNumberInRotatedArray(const std::array<int, Size>& array) noexcept
{
	return GetSmallestNumberInRotatedArrayHelper(array, 0, Size - 1);
}

int main(int argc, char* argv[])
{
	std::cout << GetSmallestNumberInRotatedArray<5>({ 5, 7, 10, 3, 4 }) << "\n";

	std::cin.get();

	return 0;
}