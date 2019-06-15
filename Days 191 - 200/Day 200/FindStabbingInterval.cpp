#include <algorithm>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>

using Interval = std::pair<unsigned int, unsigned int>;

template <typename... Intervals, typename = std::enable_if_t<(std::is_convertible_v<Intervals, Interval> && ...)>>
Interval GetStabbingInterval(const Intervals&... intervals) noexcept
{
	const std::vector<unsigned int> intervalStarts{ intervals.first... };
	const std::vector<unsigned int> intervalEnd{ intervals.second... };

	const unsigned int maxStart = *std::max_element(std::cbegin(intervalStarts), std::cend(intervalStarts));
	const unsigned int minEnd = *std::min_element(std::cbegin(intervalEnd), std::cend(intervalEnd));

	return { minEnd, maxStart };
}

template <typename T, typename U>
inline std::ostream& operator <<(std::ostream& outputStream, const std::pair<T, U>& pair) noexcept
{
	outputStream << "( " << pair.first << ", " << pair.second << " )";

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << GetStabbingInterval(Interval{ 1, 4 }, Interval{ 4, 5 }, Interval{ 7, 9 }, Interval{ 9, 12 }) << "\n";

	std::cin.get();

	return 0;
}