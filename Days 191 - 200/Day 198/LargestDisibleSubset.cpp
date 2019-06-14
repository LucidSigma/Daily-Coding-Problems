#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

std::vector<unsigned int> GetLargestDivisibleSubsetHelper(const std::vector<unsigned int>& numbers, const unsigned int previousNumber, const std::size_t currentIndex, std::vector<unsigned int> previousSubset) noexcept
{
	if (currentIndex == numbers.size())
	{
		return previousSubset;
	}

	const unsigned int currentNumber = numbers[currentIndex];
	const std::vector<unsigned int> nextSubset = GetLargestDivisibleSubsetHelper(numbers, previousNumber, currentIndex + 1, previousSubset);

	if (currentNumber % previousNumber == 0)
	{
		previousSubset.push_back(currentNumber);
		const std::vector<unsigned int> candidateSubset = GetLargestDivisibleSubsetHelper(numbers, currentNumber, currentIndex + 1, previousSubset);

		return candidateSubset.size() > nextSubset.size() ? candidateSubset : nextSubset;
	}

	return nextSubset;
}

inline std::vector<unsigned int> GetLargestDivisibleSubset(std::vector<unsigned int> numbers) noexcept
{
	std::sort(std::begin(numbers), std::end(numbers));

	return GetLargestDivisibleSubsetHelper(numbers, 1, 0, { });
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values) noexcept
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << GetLargestDivisibleSubset({ 3, 5, 10, 20, 21 }) << "\n";
	std::cout << GetLargestDivisibleSubset({ 1, 3, 6, 24 }) << "\n";

	std::cin.get();

	return 0;
}