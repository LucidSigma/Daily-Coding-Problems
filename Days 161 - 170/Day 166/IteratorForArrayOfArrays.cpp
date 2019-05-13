#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

class Iterator
{
private:
	const std::vector<std::vector<int>>& values;

	unsigned int currentIndex = 0;
	unsigned int currentSubIndex = 0;

	std::optional<int> next;

public:
	explicit Iterator(const std::vector<std::vector<int>>& values) noexcept
		: values(values), next(GetNext())
	{ }

	int Next()
	{
		if (!HasNext())
		{
			throw std::invalid_argument("Proceeded past end of iterator.");
		}
		
		int nextValue = next.value();
		next = GetNext();

		return nextValue;
	}

	inline bool HasNext() noexcept
	{
		return next != std::nullopt;
	}

private:
	std::optional<int> GetNext() noexcept
	{
		for (static unsigned int i = 0; i < values.size(); ++i)
		{
			static unsigned int j = 0;

			if (j < values[i].size())
			{
				return values[i][j++];
			}

			j = 0;
		}

		return std::nullopt;
	}
};

int main(int argc, char* argv[])
{
	const std::vector<std::vector<int>> values
	{
		{ 1, 2 },
		{ 3 },
		{ },
		{ 4, 5, 6 }
	};

	Iterator iterator{ values };

	while (iterator.HasNext())
	{
		std::cout << iterator.Next() << " ";
	}

	std::cout << "\n";

	std::cin.get();

	return 0;
}