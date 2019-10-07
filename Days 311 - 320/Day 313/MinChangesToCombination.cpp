#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <optional>
#include <tuple>
#include <unordered_set>
#include <vector>

using Combination = std::tuple<unsigned int, unsigned int, unsigned int>;

namespace std
{
	template <>
	struct hash<Combination>
	{
		inline size_t operator ()(const Combination& combination) const noexcept
		{
			const auto [a, b, c] = combination;

			return a ^ b ^ c;
		}
	};
}

std::optional<unsigned int> GetMinMovesToTarget(const Combination& start, const Combination& target, const std::unordered_set<Combination>& deadEnds)
{
	if (start == target)
	{
		return 0;
	}
	else if (deadEnds.find(start) != std::cend(deadEnds))
	{
		return std::nullopt;
	}

	const auto [start1, start2, start3] = start;
	const auto [target1, target2, target3] = target;

	if (start1 != target1)
	{
		const Combination newCombination{ target1, start2, start3 };
		
		if (const auto moveCount = GetMinMovesToTarget(newCombination, target, deadEnds); 
			moveCount.has_value())
		{
			const unsigned int key1Difference = std::abs(static_cast<int>(start1) - static_cast<int>(target1));

			return std::min(key1Difference + moveCount.value(), 10 - key1Difference + moveCount.value());
		}
	}

	if (start2 != target2)
	{
		const Combination newCombination{ start1, target2, start3 };

		if (const auto moveCount = GetMinMovesToTarget(newCombination, target, deadEnds);
			moveCount.has_value())
		{
			const unsigned int key2Difference = std::abs(static_cast<int>(start2) - static_cast<int>(target2));

			return std::min(key2Difference + moveCount.value(), 10 - key2Difference + moveCount.value());
		}
	}

	if (start3 != target3)
	{
		const Combination newCombination{ start1, start2, target3 };

		if (const auto moveCount = GetMinMovesToTarget(newCombination, target, deadEnds);
			moveCount.has_value())
		{
			const unsigned int key3Difference = std::abs(static_cast<int>(start3) - static_cast<int>(target3));

			return std::min(key3Difference + moveCount.value(), 10 - key3Difference + moveCount.value());
		}
	}

	return std::nullopt;
}

inline std::ostream& operator <<(std::ostream& outputStream, const Combination& combination)
{
	const auto [a, b, c] = combination;
	
	outputStream << "( " << a << ", " << b << ", " << c << " )";

	return outputStream;
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetMinMovesToTarget({ 0, 0, 0 }, { 1, 7, 4 }, { { 0, 0, 4 }, { 1, 0, 0 }, { 1, 2, 5 }, { 4, 0, 4 }, { 5, 0, 0 }, { 9, 9, 9 } }).value() << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}