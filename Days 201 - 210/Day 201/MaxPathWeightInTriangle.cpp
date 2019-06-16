#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

using NumberTriangle = std::vector<std::vector<int>>;

int GetMaxPathWeightInTriangleHelper(const NumberTriangle& triangle, const std::size_t rowIndex, const std::size_t level, const int currentSum) noexcept
{
	if (level == triangle.size())
	{
		return currentSum;
	}

	const int leftSum = triangle[level][rowIndex];
	const int rightSum = triangle[level][rowIndex + 1];

	const auto leftPathSum = GetMaxPathWeightInTriangleHelper(triangle, rowIndex, level + 1, currentSum + leftSum);
	const auto rightPathSum = GetMaxPathWeightInTriangleHelper(triangle, rowIndex + 1, level + 1, currentSum + rightSum);

	return std::max(leftPathSum, rightPathSum);
}

inline int GetMaxPathWeightInTriangle(const NumberTriangle& triangle) noexcept
{
	return GetMaxPathWeightInTriangleHelper(triangle, 0, 1, triangle[0][0]);
}

int main(int argc, char* argv[])
{
	std::cout << GetMaxPathWeightInTriangle({ { 1 }, { 2, 3 }, { 1, 5, 1 } }) << "\n";

	std::cin.get();

	return 0;
}