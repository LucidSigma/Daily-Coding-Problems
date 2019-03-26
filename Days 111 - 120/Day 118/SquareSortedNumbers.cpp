#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

std::vector<int> MergeSortedVectors(const std::vector<int>& a, const std::vector<int>& b) noexcept
{
	std::vector<int> mergedVector;
	mergedVector.reserve(a.size() + b.size());

	unsigned int aCounter = 0;
	unsigned int bCounter = 0;

	while (aCounter < a.size() && bCounter < b.size())
	{
		if (a[aCounter] <= b[bCounter])
		{
			mergedVector.push_back(a[aCounter]);
			aCounter++;
		}
		else
		{
			mergedVector.push_back(b[bCounter]);
			bCounter++;
		}
	}

	while (aCounter < a.size())
	{
		mergedVector.push_back(a[aCounter]);
		aCounter++;
	}

	while (bCounter < b.size())
	{
		mergedVector.push_back(b[bCounter]);
		bCounter++;
	}

	return mergedVector;
}

std::vector<int> SquareSortedNumbers(const std::vector<int>& sortedNumbers) noexcept
{
	std::vector<int> positiveSquares;
	std::vector<int> negativeSquares;

	for (const int& number : sortedNumbers)
	{
		(number >= 0 ? positiveSquares : negativeSquares).push_back(number * number);
	}

	std::reverse(std::begin(negativeSquares), std::end(negativeSquares));

	const auto mergedVector = MergeSortedVectors(positiveSquares, negativeSquares);

	return mergedVector;
}

template <typename T>
void PrintVector(const std::vector<T>& values) noexcept
{
	for (const auto& value : values)
	{
		std::cout << value << " ";
	}

	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	PrintVector(SquareSortedNumbers({ -9, -2, 0, 2, 3 }));

	std::cin.get();

	return 0;
}

