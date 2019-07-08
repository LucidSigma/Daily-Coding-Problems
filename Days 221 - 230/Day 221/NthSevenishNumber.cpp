#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

unsigned int GetNthSevenishNumber(const unsigned int n) noexcept
{
	unsigned int magnitude = 0;
	std::vector<unsigned int> sevenishNumbers;

	while (sevenishNumbers.size() < n)
	{
		const unsigned int currentSevenPower = static_cast<unsigned int>(std::pow(7, magnitude));
		std::vector<unsigned int> currentSevenishNumbers{ currentSevenPower };

		for (const auto number : sevenishNumbers)
		{
			if (sevenishNumbers.size() + currentSevenishNumbers.size() == n)
			{
				return currentSevenishNumbers.back();
			}

			currentSevenishNumbers.push_back(number + currentSevenPower);
		}

		sevenishNumbers.insert(std::cend(sevenishNumbers), std::cbegin(currentSevenishNumbers), std::cend(currentSevenishNumbers));
		++magnitude;
	}

	return sevenishNumbers.back();
}

int main(int argc, char* argv[])
{
	std::cout << GetNthSevenishNumber(4) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}