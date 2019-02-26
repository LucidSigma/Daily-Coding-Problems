#include <cmath>
#include <iostream>
#include <type_traits>
#include <vector>

struct Bishop
{
	const int x;
	const int y;

	Bishop(int x, int y) noexcept
		: x(x), y(y)
	{ }
};

template <unsigned int M, typename = std::enable_if_t<(M > 0)>>
unsigned int GetBishopAttackPairCount(const std::vector<Bishop>& bishopLocations) noexcept
{
	unsigned int pairCount = 0;
	auto bishopStack = bishopLocations;

	while (bishopStack.size() > 1)
	{
		const Bishop currentBishop = bishopStack.back();

		if (currentBishop.x < M && currentBishop.x >= 0 &&
			currentBishop.y < M && currentBishop.y >= 0)
		{
			for (auto it = bishopStack.crbegin() + 1; it != bishopStack.crend(); it++)
			{
				const Bishop otherBishop = *it;

				if (otherBishop.x >= M || otherBishop.x < 0 ||
					otherBishop.y >= M || otherBishop.y < 0)
				{
					continue;
				}
				
				const unsigned int xDifference = std::abs(currentBishop.x - otherBishop.x);
				const unsigned int yDifference = std::abs(currentBishop.y - otherBishop.y);

				if (xDifference == yDifference)
				{
					pairCount++;
				}
			}
		}

		bishopStack.pop_back();
	}

	return pairCount;
}

int main(int argc, char* argv[])
{
	const std::vector<Bishop> bishops
	{
		{ 0, 0 },
		{ 1, 2 },
		{ 2, 2 },
		{ 4, 0 }
	};

	std::cout << GetBishopAttackPairCount<5>(bishops) << "\n";

	std::cin.get();

	return 0;
}