#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

std::pair<unsigned int, std::vector<unsigned int>> GetOptimalRoundedArrayHelper(const std::vector<float>& floatArray, const std::vector<unsigned int>& roundedArray, const unsigned int roundedSum, const unsigned int difference)
{
	if (floatArray.empty())
	{
		return std::accumulate(std::cbegin(roundedArray), std::cend(roundedArray), 0) == roundedSum
			   ? std::pair{ difference, roundedArray }
			   : std::pair{ std::numeric_limits<unsigned int>::max(), std::vector<unsigned int>{ } };
	}

	const float currentNumber = floatArray.front();

	const unsigned int ceilingNumber = static_cast<unsigned int>(std::ceil(currentNumber));
	auto ceilingRoundedNumbers = roundedArray;
	ceilingRoundedNumbers.push_back(ceilingNumber);
	const auto [ceilingDifference, ceilingNumbers] = GetOptimalRoundedArrayHelper(std::vector<float>(std::cbegin(floatArray) + 1, std::cend(floatArray)), ceilingRoundedNumbers, roundedSum, difference + static_cast<unsigned int>(std::abs(ceilingNumber - currentNumber)));

	const unsigned int floorNumber = static_cast<unsigned int>(std::floor(currentNumber));
	auto floorRoundedNumbers = roundedArray;
	floorRoundedNumbers.push_back(floorNumber);
	const auto [floorDifference, floorNumbers] = GetOptimalRoundedArrayHelper(std::vector<float>(std::cbegin(floatArray) + 1, std::cend(floatArray)), floorRoundedNumbers, roundedSum, difference + static_cast<unsigned int>(std::abs(floorNumber - currentNumber)));

	return floorDifference < ceilingDifference ? std::pair{ floorDifference, floorNumbers } : std::pair{ ceilingDifference, ceilingNumbers };
}

inline std::vector<unsigned int> GetOptimalRoundedArray(const std::vector<float>& numbers)
{
	const unsigned int roundedNumberSum = std::accumulate(std::cbegin(numbers), std::cend(numbers), 0, [](const unsigned int sum, const float currentNumber)
	{
		return sum + static_cast<unsigned int>(std::round(currentNumber));
	});

	return GetOptimalRoundedArrayHelper(numbers, { }, roundedNumberSum, 0).second;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetOptimalRoundedArray({ 1.3f, 2.3f, 4.4f }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}