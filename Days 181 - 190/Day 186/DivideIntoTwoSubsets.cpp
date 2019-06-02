#include <cmath>
#include <iostream>
#include <numeric>
#include <optional>
#include <tuple>
#include <utility>
#include <vector>

std::pair<std::vector<int>, std::vector<int>> DivideIntoTwoSubsetsHelper(const std::vector<int>& firstSet, const int firstSetSum, const std::vector<int>& secondSet, const int secondSetSum, const unsigned int difference) noexcept
{
	unsigned int minDifference = difference;
	std::optional<std::tuple<std::vector<int>, int, std::vector<int>, int>> candidateSets;

	for (unsigned int i = 0; i < firstSet.size(); ++i)
	{
		const int currentFirstSetSum = firstSetSum - firstSet[i];
		const int currentSecondSetSum = secondSetSum + firstSet[i];
		const unsigned int currentDifference = std::abs(currentFirstSetSum - currentSecondSetSum);

		if (currentDifference < minDifference)
		{
			minDifference = currentDifference;

			std::vector<int> newFirstSet = firstSet;
			newFirstSet.erase(std::cbegin(newFirstSet) + i);

			std::vector<int> newSecondSet = secondSet;
			newSecondSet.push_back(firstSet[i]);

			candidateSets = { newFirstSet, currentFirstSetSum, newSecondSet, currentSecondSetSum };
		}
	}

	return candidateSets == std::nullopt
		   ? std::pair<std::vector<int>, std::vector<int>>{ firstSet, secondSet }
		   : DivideIntoTwoSubsetsHelper(std::get<0>(candidateSets.value()), std::get<1>(candidateSets.value()), std::get<2>(candidateSets.value()), std::get<3>(candidateSets.value()), minDifference);
}

inline std::pair<std::vector<int>, std::vector<int>> DivideIntoTwoSubsets(const std::vector<int>& numbers) noexcept
{
	const int sum = std::accumulate(std::cbegin(numbers), std::cend(numbers), 0);
	
	return DivideIntoTwoSubsetsHelper(numbers, sum, { }, 0, sum);
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values) noexcept
{
	outputStream << "[ ";

	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	outputStream << "]";

	return outputStream;
}

template <typename T, typename U>
inline std::ostream& operator <<(std::ostream& outputStream, const std::pair<T, U>& pair) noexcept
{
	outputStream << "( " << pair.first << ", " << pair.second << " )";

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << DivideIntoTwoSubsets({ 5, 10, 15, 20, 25 }) << "\n";

	std::cin.get();

	return 0;
}