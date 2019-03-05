#include <iostream>
#include <iterator>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

class TimeMap
{
private:
	std::unordered_map<int, std::pair<std::vector<int>, std::vector<int>>> timeMap;

public:
	void Set(int key, int value, int time) noexcept
	{
		if (timeMap.find(key) == std::end(timeMap))
		{
			timeMap[key] = { {time }, { value } };

			return;
		}

		auto&[times, values] = timeMap[key];
		unsigned int insertionIndex = GetInsertionIndex(times, time);

		times.insert(std::begin(times) + insertionIndex, time);
		values.insert(std::begin(values) + insertionIndex, value);
	}

	std::optional<int> Get(int key, int time)
	{
		if (timeMap.find(key) == std::end(timeMap))
		{
			throw std::invalid_argument("Key not in map.");
		}

		const auto&[times, values] = timeMap[key];
		unsigned int insertionIndex = GetInsertionIndex(times, time);

		if (insertionIndex == 0)
		{
			return std::nullopt;
		}

		return values[insertionIndex - 1];
	}

private:
	unsigned int GetInsertionIndex(const std::vector<int> times, int time) noexcept
	{
		for (unsigned int i = 0; i < times.size(); i++)
		{
			if (time < times[i])
			{
				return i;
			}
		}

		return times.size();
	}
};

int main(int argc, char* argv[])
{
	TimeMap timeMapA;

	timeMapA.Set(1, 1, 0);
	timeMapA.Set(1, 2, 2);
	std::cout << timeMapA.Get(1, 1).value() << "\n";
	std::cout << timeMapA.Get(1, 3).value() << "\n\n";

	TimeMap timeMapB;

	timeMapB.Set(1, 1, 5);

	if (timeMapB.Get(1, 0).has_value())
	{
		std::cout << timeMapB.Get(1, 0).value() << "\n";
	}
	else
	{
		std::cout << "null\n";
	}

	std::cout << timeMapB.Get(1, 10).value() << "\n\n";

	TimeMap timeMapC;

	timeMapC.Set(1, 1, 0);
	timeMapC.Set(1, 2, 0);
	std::cout << timeMapC.Get(1, 0).value() << "\n";

	std::cin.get();

	return 0;
}