#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <unordered_map>

class ConstantCounter
{
private:
	std::unordered_map<unsigned int, unsigned int> m_counts;

	unsigned int m_min = std::numeric_limits<unsigned int>::max();
	unsigned int m_max = std::numeric_limits<unsigned int>::min();

public:
	ConstantCounter() = default;
	~ConstantCounter() noexcept = default;

	void Plus(const unsigned int key)
	{
		if (m_counts.find(key) == std::cend(m_counts))
		{
			m_counts[key] = 0;
		}

		++m_counts[key];
		UpdateMinAndMax(m_counts[key]);
	}

	void Minus(const unsigned int key)
	{
		if (m_counts.find(key) != std::cend(m_counts))
		{
			--m_counts[key];

			if (m_counts[key] == 0)
			{
				m_counts.erase(key);
			}
			else
			{
				UpdateMinAndMax(m_counts[key]);
			}

		}
	}

	inline unsigned int GetMin() const noexcept { return m_min; }
	inline unsigned int GetMax() const noexcept { return m_max; }

private:
	void UpdateMinAndMax(const unsigned int newValue)
	{
		m_min = std::min(m_min, newValue);
		m_max = std::max(m_max, newValue);
	}
};

int main(const int argc, const char* const argv[])
{
	ConstantCounter counter;
	counter.Plus(1);
	counter.Plus(1);
	counter.Plus(1);
	counter.Plus(2);
	counter.Plus(2);
	counter.Plus(3);
	counter.Plus(4);
	counter.Plus(4);
	counter.Plus(5);

	std::cout << counter.GetMin() << "\n";
	std::cout << counter.GetMax() << "\n";

	counter.Minus(1);
	counter.Minus(1);
	counter.Minus(5);

	std::cout << counter.GetMin() << "\n";
	std::cout << counter.GetMax() << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}