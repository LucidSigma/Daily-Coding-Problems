#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

std::vector<std::pair<unsigned int, unsigned int>> MergeOverlappingIntervals(const std::vector<std::pair<unsigned int, unsigned int>>& intervals) noexcept
{
	std::unordered_set<unsigned int> starts;
	std::unordered_set<unsigned int> ends;

	for (const auto[start, end] : intervals)
	{
		starts.insert(start);
		ends.insert(end);
	}

	const unsigned int minStart = *std::min_element(starts.begin(), starts.end());
	const unsigned int maxEnd = *std::max_element(ends.begin(), ends.end());
	int current = 0;
	std::vector<int> statuses { current };

	for (unsigned int i = minStart; i < maxEnd + 1; i++)
	{
		if (std::find(ends.begin(), ends.end(), i) != ends.end())
		{
			current--;
		}

		if (std::find(starts.begin(), starts.end(), i) != starts.end())
		{
			current++;
		}

		statuses.push_back(current);
	}

	unsigned int start = 0;
	unsigned int end = 0;
	std::vector<std::pair<unsigned int, unsigned int>> merged;

	for (unsigned int i = 1; i < statuses.size(); i++)
	{
		if (statuses[i] != 0 && statuses[i - 1] == 0)
		{
			start = i;
		}

		if (statuses[i] == 0 && statuses[i - 1] != 0)
		{
			end = i;
			merged.emplace_back(start, end);

			start = 0;
			end = 0;
		}
	}

	return merged;
}

template <typename T, typename U>
void PrintVectorOfPairs(const std::vector<std::pair<T, U>>& pairs) noexcept
{
	for (const auto[a, b] : pairs)
	{
		std::cout << "[ " << a << ", " << b << " ]\n";
	}
}

int main(int argc, char* argv[])
{
	std::vector<std::pair<unsigned int, unsigned int>> intervals
	{
		{ 1, 3 },
		{ 5, 8 },
		{ 4, 10 },	
		{ 20, 25 }	
	};

	PrintVectorOfPairs(MergeOverlappingIntervals(intervals));

	std::cin.get();

	return 0;
}
