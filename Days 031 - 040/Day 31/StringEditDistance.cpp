#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
constexpr const T& MinOfThree(const T& a, const T& b, const T& c) noexcept
{
	return std::min(std::min(a, b), c);
}

unsigned int EditDistance(const std::string& source, const std::string& destination) noexcept
{
	std::vector<std::vector<unsigned int>> solutions(source.length() + 1, std::vector<unsigned int>(destination.length() + 1));

	for (unsigned int i = 0; i < solutions.size(); i++)
	{
		for (unsigned int j = 0; j < solutions[i].size(); j++)
		{
			if (i == 0)
			{
				solutions[i][j] = j;
			}
			else if (j == 0)
			{
				solutions[i][j] = i;
			}
			else if (source[i - 1] == destination[j - 1])
			{
				solutions[i][j] = solutions[i - 1][j - 1];
			}
			else
			{
				solutions[i][j] = MinOfThree(solutions[i][j - 1], solutions[i - 1][j], solutions[i - 1][j - 1]) + 1;
			}
		}
	}

	return solutions[source.length()][destination.length()];
}

int main(int argc, const char* argv[])
{
	std::cout << EditDistance("kitten", "sitting") << "\n";

	std::cin.get();

	return 0;
}