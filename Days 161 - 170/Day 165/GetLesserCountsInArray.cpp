#include <iostream>
#include <vector>

std::vector<unsigned int> GetLesserCountArray(const std::vector<int>& numbers) noexcept
{
	std::vector<unsigned int> lesserCounts;
	lesserCounts.reserve(numbers.size());

	for (unsigned int i = 0; i < numbers.size() - 1; ++i)
	{
		unsigned int currentLesserCount = 0;

		for (unsigned int j = i + 1; j < numbers.size(); ++j)
		{
			if (numbers[j] < numbers[i])
			{
				++currentLesserCount;
			}
		}

		lesserCounts.push_back(currentLesserCount);
	}

	return lesserCounts.push_back(0), lesserCounts;
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
	PrintVector(GetLesserCountArray({ 3, 4, 9, 6, 1 }));

	std::cin.get();

	return 0;
}