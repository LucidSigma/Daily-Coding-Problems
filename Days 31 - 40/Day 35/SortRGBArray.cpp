#include <array>
#include <iostream>
#include <utility>

template <typename T, unsigned int Size>
int PullElementsToFront(std::array<T, Size>& array, unsigned int startIndex, unsigned int endIndex, const T& element) noexcept
{
	int currentIndex = -1;

	while (startIndex < endIndex)
	{
		if (array[startIndex] == element)
		{
			currentIndex = startIndex;
			startIndex++;
		}
		else if (array[endIndex] != element)
		{
			endIndex--;
		}
		else
		{
			currentIndex = startIndex;

			std::swap(array[startIndex], array[endIndex]);
		}
	}

	return currentIndex;
}

template <unsigned int Size>
std::array<char, Size> SortRGBArray(const std::array<char, Size>& array)
{
	static constexpr unsigned int TOTAL_ELEMENTS = 3;
	static constexpr char ELEMENTS[TOTAL_ELEMENTS] { 'R', 'G', 'B' };

	std::array<char, Size> sortedArray(array);
	int partition = -1;

	for (unsigned int i = 0; i < TOTAL_ELEMENTS - 1; i++)
	{
		partition = PullElementsToFront(sortedArray, partition + 1, sortedArray.size() - 1, ELEMENTS[i]);
	}

	return sortedArray;
}

template <typename T, unsigned int Size>
void PrintArray(const std::array<T, Size>& array)
{
	for (const auto& value : array)
	{
		std::cout << value << " ";
	}

	std::cout << "\n";
}

int main(int argc, const char* argv[])
{
	std::array<char, 7> array { 'G', 'B', 'R', 'R', 'B', 'R', 'G' };

	std::cout << "Original array: ";
	PrintArray(array);

	std::cout << "  Sorted array: ";
	PrintArray(SortRGBArray(array));

	std::cin.get();

	return 0;
}