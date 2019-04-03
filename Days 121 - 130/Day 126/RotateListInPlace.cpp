#include <algorithm>
#include <array>
#include <iostream>

template <unsigned int Size>
void RotateList(std::array<int, Size>& array, int rotationAmount) noexcept
{
	if (rotationAmount % Size == 0)
	{
		return;
	}

	rotationAmount %= static_cast<int>(Size);

	if (rotationAmount > 0)
	{
		for (unsigned int i = 0; i < Size - rotationAmount; i++)
		{
			std::swap(array[i], array[i + rotationAmount]);
		}
	}
	else
	{
		for (int i = Size - 1; i >= 0 - rotationAmount; i--)
		{
			std::swap(array[i], array[i + rotationAmount]);
		}
	}
}

template <typename T, unsigned int Size>
void PrintArray(const std::array<T, Size>& array) noexcept
{
	for (const auto& value : array)
	{
		std::cout << value << " ";
	}

	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	std::array<int, 6> numbers { 1, 2, 3, 4, 5, 6 };

	RotateList(numbers, 2);
	PrintArray(numbers);

	RotateList(numbers, -2);
	PrintArray(numbers);

	std::cin.get();

	return 0;
}