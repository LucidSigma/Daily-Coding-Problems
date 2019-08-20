#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

std::vector<std::pair<bool, unsigned int>> GetSeatStatuses(const std::vector<unsigned int>& linesOfCode)
{
	bool isAscending = linesOfCode[1] > linesOfCode[0];
	unsigned int previousSeat = linesOfCode.front();
	unsigned int currentBonus = 0;
	std::vector<std::pair<bool, unsigned int>> seatStatuses;

	for (size_t i = 1; i < linesOfCode.size(); ++i)
	{
		if ((isAscending && linesOfCode[i] < previousSeat) || (!isAscending && linesOfCode[i] > previousSeat))
		{
			seatStatuses.emplace_back(isAscending, i - currentBonus + 1);
			currentBonus = i + 1;
			isAscending = !isAscending;
		}

		previousSeat = linesOfCode[i];
	}

	return seatStatuses.emplace_back(isAscending, linesOfCode.size() - currentBonus), seatStatuses;
}

std::vector<unsigned int> GenerateBonuses(const std::vector<unsigned int>& linesOfCode)
{
	const auto seatStatuses = GetSeatStatuses(linesOfCode);
	std::vector<unsigned int> bonuses;

	for (const auto [isAscending, bonusSize] : seatStatuses)
	{
		std::vector<unsigned int> currentBonus(bonusSize);
		std::iota(std::begin(currentBonus), std::end(currentBonus), 1);

		if (!isAscending)
		{
			std::reverse(std::begin(currentBonus), std::end(currentBonus));
		}

		bonuses.insert(std::cend(bonuses), std::cbegin(currentBonus), std::cend(currentBonus));
	}

	return bonuses;
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

int main(int argc, char* argv[])
{
	std::cout << GenerateBonuses({ 10, 40, 200, 1000, 60, 30 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}