#include <iostream>
#include <utility>
#include <vector>

std::pair<std::vector<int>, unsigned int> Merge(const std::pair<std::vector<int>, unsigned int>& firstHalf, const std::pair<std::vector<int>, unsigned int>& secondHalf) noexcept
{
	unsigned int i = 0;
	unsigned int j = 0;

	std::vector<int> mergedVector;
	mergedVector.reserve(firstHalf.first.size() + secondHalf.first.size());

	auto[firstVector, firstInversions] = firstHalf;
	auto[secondVector, secondInversions] = secondHalf;

	unsigned int totalInversions = firstInversions + secondInversions;

	while ((i < firstVector.size()) && (j < secondVector.size()))
	{
		if (firstVector[i] < secondVector[j])
		{
			mergedVector.push_back(firstVector[i]);

			i++;
		}
		else
		{
			mergedVector.push_back(secondVector[j]);
			totalInversions += firstVector.size() - i;

			j++;
		}
	}

	while (i < firstVector.size())
	{
		mergedVector.push_back(firstVector[i]);

		i++;
	}

	while (j < secondVector.size())
	{
		mergedVector.push_back(secondVector[j]);

		j++;
	}

	return std::make_pair(mergedVector, totalInversions);
}

std::pair<std::vector<int>, unsigned int> MergeSort(const std::vector<int>& numbers) noexcept
{
	if (numbers.empty() || numbers.size() == 1)
	{
		return std::make_pair(numbers, 0);
	}

	unsigned int midpoint = numbers.size() / 2;

	return Merge(MergeSort(std::vector<int>(numbers.begin(), numbers.begin() + midpoint)), MergeSort(std::vector<int>(numbers.begin() + midpoint, numbers.end())));
}

unsigned int GetTotalInversions(const std::vector<int>& numbers) noexcept
{
	return MergeSort(numbers).second;
}

int main(int argc, const char* argv[])
{
	std::cout << GetTotalInversions({ 2, 4, 1, 3, 5 }) << "\n";
	std::cout << GetTotalInversions({ 5, 4, 3, 2, 1 }) << "\n";

	std::cin.get();

	return 0;
}