#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

class PrefixMapSum
{
private:
	std::map<std::string, int> m_values;

public:
	PrefixMapSum() = default;
	~PrefixMapSum() noexcept = default;

	inline void Insert(const std::string& key, const int value) noexcept
	{
		m_values[key] = value;
	}

	int Sum(const std::string& prefix) const noexcept
	{
		int sum = 0;

		for (const auto& [key, value] : m_values)
		{
			if (key.find(prefix) == 0)
			{
				sum += value;
			}
		}

		return sum;
	}
};

int main(int argc, char* argv[])
{
	PrefixMapSum prefixMapSum;

	prefixMapSum.Insert("columnar", 3);
	std::cout << prefixMapSum.Sum("col") << "\n";

	prefixMapSum.Insert("column", 2);
	std::cout << prefixMapSum.Sum("col") << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}