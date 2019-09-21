#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <vector>

using Apple = unsigned int;

class AppleSet
{
private:
	std::unordered_map<Apple, unsigned int> m_appleTypeCounts;

public:
	AppleSet() = default;
	~AppleSet() noexcept = default;

	void AddApple(const Apple type)
	{
		if (m_appleTypeCounts.find(type) == std::cend(m_appleTypeCounts))
		{
			m_appleTypeCounts[type] = 0;
		}

		++m_appleTypeCounts[type];
	}

	void RemoveApple(const Apple type)
	{
		--m_appleTypeCounts[type];

		if (m_appleTypeCounts[type] == 0)
		{
			m_appleTypeCounts.erase(type);
		}
	}

	unsigned int TotalApples() const
	{
		unsigned int total = 0;

		for (const auto [_, count] : m_appleTypeCounts)
		{
			total += count;
		}

		return total;
	}

	inline size_t GetSize() const noexcept { return m_appleTypeCounts.size(); }
};

unsigned int GetLongestPortionLengthHelper(const AppleSet& appleSet, const std::vector<Apple>& apples)
{
	if (appleSet.GetSize() == 2)
	{
		return appleSet.TotalApples();
	}

	if (apples.empty())
	{
		return 0;
	}

	auto firstAppleSet = appleSet;
	firstAppleSet.RemoveApple(apples.front());
	const unsigned int firstResult = GetLongestPortionLengthHelper(firstAppleSet, std::vector<Apple>(std::cbegin(apples) + 1, std::cend(apples)));

	auto secondAppleSet = appleSet;
	secondAppleSet.RemoveApple(apples.back());
	const unsigned int secondResult = GetLongestPortionLengthHelper(secondAppleSet, std::vector<Apple>(std::cbegin(apples), std::cend(apples) - 1));

	return std::max(firstResult, secondResult);
}

unsigned int GetLongestPortionLength(const std::vector<Apple>& apples)
{
	AppleSet appleSet;

	for (const auto apple : apples)
	{
		appleSet.AddApple(apple);
	}

	return GetLongestPortionLengthHelper(appleSet, apples);
}

int main(int argc, char* argv[])
{
	std::cout << GetLongestPortionLength({ 2, 1, 2, 3, 3, 1, 3, 5 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}