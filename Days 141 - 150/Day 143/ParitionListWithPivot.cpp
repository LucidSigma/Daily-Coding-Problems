#include <algorithm>
#include <iostream>
#include <vector>

unsigned int PartitionListOnPivotHelper(const int pivot, unsigned int forwardIndex, unsigned int backwardIndex, std::vector<int>& numbers) noexcept
{
	while (forwardIndex < backwardIndex)
	{
		if (numbers[forwardIndex] >= pivot && numbers[backwardIndex] < pivot)
		{
			std::swap(numbers[forwardIndex], numbers[backwardIndex]);
		}
		else
		{
			if (numbers[forwardIndex] < pivot)
			{
				forwardIndex++;
			}
			
			if (numbers[backwardIndex] >= pivot)
			{
				backwardIndex--;
			}
		}
	}

	return numbers[forwardIndex] < pivot && (forwardIndex + 1) < numbers.size() ? forwardIndex + 1 : forwardIndex;
}

std::vector<int> PartitionListOnPivot(const int pivot, std::vector<int> numbers) noexcept
{
	const unsigned int midpoint = PartitionListOnPivotHelper(pivot, 0, numbers.size() - 1, numbers);
	PartitionListOnPivotHelper(pivot + 1, midpoint, numbers.size() - 1, numbers);

	return numbers;
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
	const std::vector<int> numbers { 9, 12, 3, 5, 14, 10, 10 };
	
	std::cout << "Before paritiion: ";
	PrintVector(numbers);

	const std::vector<int> paritionedNumbers = PartitionListOnPivot(10, numbers);

	std::cout << " After partition: ";
	PrintVector(paritionedNumbers);

	std::cin.get();

	return 0;
}