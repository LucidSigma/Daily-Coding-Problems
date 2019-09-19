#include <cstdlib>
#include <iostream>
#include <vector>

std::vector<unsigned int> GetKthPascalsTriangleRowHelper(const unsigned int k, std::vector<unsigned int> row)
{
	if (row.empty())
	{
		row = std::vector<unsigned int>(k, 0);
		row.front() = 1;
	}

	if (k == 1)
	{
		return row;
	}

	row = GetKthPascalsTriangleRowHelper(k - 1, row);

	for (int i = row.size() - 1; i > 0; --i)
	{
		row[i] += row[i - 1];
	}

	return row;
}

inline std::vector<unsigned int> GetKthPascalsTriangleRow(const unsigned int k)
{
	return GetKthPascalsTriangleRowHelper(k, { });
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	for (unsigned int i = 1; i <= 10; ++i)
	{
		std::cout << GetKthPascalsTriangleRow(i) << "\n";
	}

	std::cin.get();

	return EXIT_SUCCESS;
}