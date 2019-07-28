#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>

class HourlySubscriberCount
{
private:
	static constexpr size_t s_HourCount = 24u;

	std::array<unsigned int, s_HourCount> m_hourlyCounts{ 0 };

public:
	HourlySubscriberCount() = default;
	~HourlySubscriberCount() noexcept = default;

	void Update(const size_t hour, const unsigned int value)
	{
		m_hourlyCounts[hour] = value;
	}

	unsigned int Query(const size_t start, const size_t end) const
	{
		return std::accumulate(std::cbegin(m_hourlyCounts) + start, std::cbegin(m_hourlyCounts) + end + 1, 0);
	}
};

int main(int argc, char* argv[])
{
	std::random_device randomSeed;
	std::mt19937 randomEngine(randomSeed());
	std::uniform_int_distribution<int> randomRange(0, 100);

	HourlySubscriberCount hourlySubscriberCount;

	for (size_t i = 0; i < 24; ++i)
	{
		hourlySubscriberCount.Update(i, randomRange(randomEngine));
	}

	std::cout << hourlySubscriberCount.Query(11, 18) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}