#include <algorithm>
#include <iostream>
#include <iterator>
#include <optional>
#include <vector>

inline std::vector<int> Reverse(std::vector<int> list, unsigned int i, unsigned int j)
{
	return std::reverse(std::begin(list) + i, std::begin(list) + j + 1), list;
}

std::vector<int> MergeSortedSubranges(const std::vector<int>& subrangeA, const std::vector<int>& subrangeB) noexcept
{
	std::vector<int> mergedSubranges;
	unsigned int indexA = 0;
	unsigned int indexB = 0;

	while (indexA < subrangeA.size() && indexB < subrangeB.size())
	{
		if (subrangeA[indexA] <= subrangeB[indexB])
		{
			mergedSubranges.push_back(subrangeA[indexA]);
			indexA++;
		}
		else
		{
			mergedSubranges.push_back(subrangeB[indexB]);
			indexB++;
		}
	}

	while (indexA < subrangeA.size())
	{
		mergedSubranges.push_back(subrangeA[indexA]);
		indexA++;
	}

	while (indexB < subrangeB.size())
	{
		mergedSubranges.push_back(subrangeB[indexB]);
		indexB++;
	}

	return mergedSubranges;
}

std::vector<int> ReverseSort(const std::vector<int>& list) noexcept
{
	std::optional<unsigned int> start{ };
	std::optional<unsigned int> end{ };
	int previousEndIndex = -1;
	std::vector<std::vector<int>> sortedSubranges;

	for (unsigned int i = 1; i < list.size(); i++)
	{
		if (list[i] < list[i - 1])
		{
			if (start == std::nullopt)
			{
				std::vector<int> currentSubrange(std::cbegin(list) + (static_cast<unsigned int>(previousEndIndex) + 1), std::cbegin(list) + i - 1);

				if (!currentSubrange.empty())
				{
					sortedSubranges.push_back(currentSubrange);
				}

				start = i - 1;
			}
		}
		else if (start != std::nullopt)
		{
			end = i - 1;

			if (end > start)
			{
				sortedSubranges.push_back(Reverse(list, start.value(), end.value()));
			}
		}
	}

	if (start != std::nullopt)
	{
		end = list.size() - 1;

		if (end > start)
		{
			sortedSubranges.push_back(Reverse(list, start.value(), end.value()));
		}
	}
	else
	{
		std::vector<int> currentSubrange(std::cbegin(list) + (static_cast<unsigned int>(previousEndIndex) + 1), std::cend(list));

		if (!currentSubrange.empty())
		{
			sortedSubranges.push_back(currentSubrange);
		}
	}

	std::vector<int> mergedSubranges;

	for (const auto& subrange : sortedSubranges)
	{
		mergedSubranges = MergeSortedSubranges(mergedSubranges, subrange);
	}

	return mergedSubranges;
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
	PrintVector(ReverseSort({ 0, 5, 8, 1, 9, 2, 4, 3, 7, 6 }));

	std::cin.get();

	return 0;
}