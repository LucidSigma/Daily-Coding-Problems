#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

struct Node
{
	int value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(const int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr) noexcept
		: value(value), left(left), right(right)
	{ }
};

void GetMinimumTreePathSumHelper(const std::shared_ptr<Node>& node, int sum, std::vector<int>& pathSums) noexcept
{
	sum += node->value;

	if (node->left == nullptr && node->right == nullptr)
	{
		pathSums.push_back(sum);
	}
	else
	{
		if (node->left != nullptr)
		{
			GetMinimumTreePathSumHelper(node->left, sum, pathSums);
		}

		if (node->right != nullptr)
		{
			GetMinimumTreePathSumHelper(node->right, sum, pathSums);
		}
	}
}

int GetMinimumTreePathSum(const std::shared_ptr<Node>& root) noexcept
{
	std::vector<int> sums;
	GetMinimumTreePathSumHelper(root, 0, sums);

	return *std::min_element(std::cbegin(sums), std::cend(sums));
}

int main(int argc, char* argv[])
{
	const auto nodeNeg1 = std::make_shared<Node>(-1);
	const auto node1 = std::make_shared<Node>(1, nodeNeg1);
	const auto node5b = std::make_shared<Node>(5, nullptr, node1);
	const auto node2 = std::make_shared<Node>(2);
	const auto node5a = std::make_shared<Node>(5, nullptr, node2);
	const auto root = std::make_shared<Node>(10, node5a, node5b);

	std::cout << GetMinimumTreePathSum(root) << "\n";

	std::cin.get();

	return 0;
}