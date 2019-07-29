#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <utility>
#include <vector>

inline int Sum(const std::vector<int>& numbers)
{
	return  std::accumulate(std::cbegin(numbers), std::cend(numbers), 0);
}

std::pair<std::vector<int>, int> GetMaxSumFromMinPartitionsHelper(const std::vector<int>& numbers, const unsigned int partitionCount)
{
	if (partitionCount == 1)
	{
		return { { numbers }, Sum(numbers) };
	}

	int minNumber = std::numeric_limits<int>::max();
	int minSum = std::numeric_limits<int>::max();
	std::vector<int> minPartition;

	for (unsigned int i = 0; i < numbers.size(); ++i)
	{
		auto leftPartition = std::vector<int>(std::cbegin(numbers), std::cbegin(numbers) + i);
		const int leftSum = Sum(leftPartition);
		const auto [rightPartition, rightSum] = GetMaxSumFromMinPartitionsHelper(std::vector<int>(std::cbegin(numbers) + i, std::cend(numbers)), partitionCount - 1);
	
		leftPartition.insert(std::cend(leftPartition), std::cbegin(rightPartition), std::cend(rightPartition));
		
		if (const int candidateSum = leftSum + rightSum;
			candidateSum < minNumber)
		{
			minNumber = candidateSum;
			minSum = candidateSum;
			minPartition = leftPartition;
		}
	}

	return { minPartition, minSum };
}

inline int GetMaxSumFromMinPartitions(const std::vector<int>& numbers, const unsigned int partitionCount)
{
	return GetMaxSumFromMinPartitionsHelper(numbers, partitionCount).second;
}

int main(int argc, char* argv[])
{
	std::cout << GetMaxSumFromMinPartitions({ 5, 1, 2, 7, 3, 4 }, 3) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}