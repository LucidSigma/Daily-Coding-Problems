#include <array>
#include <iostream>

template <unsigned int Size>
unsigned int GetIndexFromRotatedArrayHelper(const std::array<int, Size>& array, int number, unsigned first, unsigned int last) noexcept
{
	unsigned int midIndex = first + ((last - first) / 2);

	if (array[midIndex] == number)
	{
		return midIndex;
	}
	else if (array[midIndex] > number)
	{
		return array[first] >= number 
			? GetIndexFromRotatedArrayHelper(array, number, first, midIndex) 
			: GetIndexFromRotatedArrayHelper(array, number, midIndex, last);
	}
	else if (array[midIndex] < number)
	{
		return array[first] <= number 
			? GetIndexFromRotatedArrayHelper(array, number, first, midIndex) 
			: GetIndexFromRotatedArrayHelper(array, number, midIndex, last);
	}
}

template <unsigned int Size>
unsigned int GetIndexFromRotatedArray(const std::array<int, Size>& rotatedArray, int number) noexcept
{
	return GetIndexFromRotatedArrayHelper(rotatedArray, number, 0, rotatedArray.size());
}

int main(int argc, char* argv[])
{
	std::cout << GetIndexFromRotatedArray<6>({ 13, 18, 25, 2, 8, 10 }, 8) << "\n";

	std::cin.get();

	return 0;
}