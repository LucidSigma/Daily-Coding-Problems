#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>

struct Node
{
	int value;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr) noexcept
		: value(value), left(left), right(right)
	{ }
};

int GetMaxTreePathSumHelper(const std::shared_ptr<Node>& node, int currentMaxSum, int overallMaxSum) noexcept
{
	if (node == nullptr)
	{
		return overallMaxSum;
	}

	currentMaxSum = std::max(node->value, currentMaxSum + node->value);
	overallMaxSum = std::max(overallMaxSum, currentMaxSum);

	int leftTreePathSum = GetMaxTreePathSumHelper(node->left, currentMaxSum, overallMaxSum);
	int rightTreePathSum = GetMaxTreePathSumHelper(node->right, currentMaxSum, overallMaxSum);

	return std::max({ overallMaxSum, leftTreePathSum, rightTreePathSum });
}

inline int GetMaxTreePathSum(const std::shared_ptr<Node>& root) noexcept
{
	return GetMaxTreePathSumHelper(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::min());
}

int main(int argc, char* argv[])
{
	auto leftRight = std::make_shared<Node>(6);
	auto left = std::make_shared<Node>(5, nullptr, leftRight);

	auto rightLeft = std::make_shared<Node>(10);
	auto rightRight = std::make_shared<Node>(9);
	auto right = std::make_shared<Node>(4, rightLeft, rightRight);

	auto root = std::make_shared<Node>(-8, left, right);

	std::cout << GetMaxTreePathSum(root) << "\n";

	std::cin.get();

	return 0;
}