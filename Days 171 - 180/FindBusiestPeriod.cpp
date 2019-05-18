#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct GroupData
{
	unsigned long long timestamp;
	unsigned int count;
	std::string type;
};

std::pair<unsigned long long, unsigned long long> GetBusiestPeriod(const std::vector<GroupData>& dataEntries) noexcept
{
	std::unordered_map<unsigned long long, unsigned int> entries;
	std::unordered_map<unsigned long long, unsigned int> exits;

	unsigned long long maxTime = 0;
	unsigned long long minTime = std::numeric_limits<unsigned long long>::max();

	for (const auto& [timestamp, count, type] : dataEntries)
	{
		(type == "enter" ? entries : exits)[timestamp] = count;

		if (timestamp < minTime)
		{
			minTime = timestamp;
		}
		else if (timestamp > maxTime)
		{
			maxTime = timestamp;
		}
	}

	unsigned int personCount = 0;
	unsigned int maxPersonCount = 0;
	unsigned long long startTime = 0;
	unsigned long long endTime = 0;

	for (unsigned long long time = minTime; time <= maxTime; ++time)
	{
		if (entries.find(time) != std::cend(entries))
		{
			personCount += entries[time];

			if (personCount > maxPersonCount)
			{
				maxPersonCount = personCount;
				startTime = time;
			}
		}

		if (exits.find(time) != std::cend(exits))
		{
			if (personCount == maxPersonCount)
			{
				endTime = time;
			}

			personCount -= exits[time];
		}
	}

	return { startTime, endTime };
}

template <typename T, typename U>
inline std::ostream& operator <<(std::ostream& outputStream, const std::pair<T, U>& pair) noexcept
{
	outputStream << "( " << pair.first << ", " << pair.second << " )";

	return outputStream;
}

int main(int argc, char* argv[])
{
	const std::vector<GroupData> dataEntries
	{
		{ 1526579928, 3, "enter" },
		{ 1526580757, 2, "enter" },
		{ 1526581038, 4, "exit" },
		{ 1526581503, 5, "enter" },
		{ 1526582349, 6, "exit" },
		{ 1526585093, 2, "enter" },
		{ 1526586382, 2, "exit" }
	};

	std::cout << GetBusiestPeriod(dataEntries) << "\n";

	std::cin.get();

	return 0;
}