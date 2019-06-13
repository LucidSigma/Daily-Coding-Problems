#include <array>
#include <cstddef>
#include <iostream>

template <typename T, std::size_t Size>
inline void RotateArrayHelper(std::array<T, Size>& array, const unsigned int k, const std::size_t currentIndex, const T& currentElement, const unsigned int swapCount) noexcept
{
	if (swapCount == Size)
	{
		return;
	}

	const std::size_t nextIndex = (currentIndex + k) % Size;
	const T nextElement = array[nextIndex];
	array[nextIndex] = currentElement;

	RotateArrayHelper(array, k, nextIndex, nextElement, swapCount + 1);
}

template <typename T, std::size_t Size>
inline void RotateArray(std::array<T, Size>& array, const unsigned int k) noexcept
{
	if (k == 0)
	{
		return;
	}

	RotateArrayHelper(array, k, 0, array[0], 0);
}

template <typename T, std::size_t Size>
std::ostream& operator <<(std::ostream& outputStream, const std::array<T, Size>& array) noexcept
{
	for (const auto element : array)
	{
		outputStream << element << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::array<int, 5> array{ 1, 2, 3, 4, 5 };
	std::cout << array << "\n";

	RotateArray(array, 2);
	std::cout << array << "\n";

	std::cin.get();

	return 0;
}