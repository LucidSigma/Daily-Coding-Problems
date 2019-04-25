#include <array>
#include <iostream>
#include <stdexcept>

template <unsigned int Size>
std::array<int, Size + 1> PreprocessArray(const std::array<int, Size>& numbers) noexcept
{
	int total = 0;
	std::array<int, Size + 1> cumulativeSums;
	cumulativeSums[0] = total;
	
	for (unsigned int i = 0; i < Size; i++)
	{
		total += numbers[i];
		cumulativeSums[i + 1] = total;
	}

	return cumulativeSums;
}

template <unsigned int Size>
int Sum(const std::array<int, Size>& numbers, const unsigned int start, const unsigned int end)
{
	std::array<int, Size + 1> cumulativeSums = PreprocessArray(numbers);

	if (start < 0 || end > Size || start > end)
	{
		throw std::invalid_argument("Invalid index passed as argument.");
	}

	return cumulativeSums[end] - cumulativeSums[start];
}

int main(int argc, char* argv[])
{
	std::cout << Sum<5>({ 1, 2, 3, 4, 5 }, 1, 3) << "\n";

	std::cin.get();

	return 0;
}