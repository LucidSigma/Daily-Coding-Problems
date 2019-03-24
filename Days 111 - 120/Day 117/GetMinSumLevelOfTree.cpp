#include <algorithm>
#include <iostream>
#include <limits>
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

unsigned int GetMinLevelSumOfTreeHelper(const std::vector<std::shared_ptr<Node>>& levelNodes, unsigned int level, int totalMinSum, int totalMinLevel) noexcept
{
	int minLevel = totalMinLevel;

	if (!levelNodes.empty())
	{
		int currentSum = 0;
		std::vector<std::shared_ptr<Node>> nextLevelNodes;

		for (const auto& node : levelNodes)
		{
			currentSum += node->value;

			if (node->left != nullptr)
			{
				nextLevelNodes.push_back(node->left);
			}

			if (node->right != nullptr)
			{
				nextLevelNodes.push_back(node->right);
			}
		}

		minLevel = currentSum < totalMinSum ? level : minLevel;
		minLevel = GetMinLevelSumOfTreeHelper(nextLevelNodes, level + 1, std::min(currentSum, totalMinSum), minLevel);
	}

	return minLevel;
}

unsigned int GetMinLevelSumOfTree(const std::shared_ptr<Node>& root) noexcept
{
	return GetMinLevelSumOfTreeHelper({ root }, 0, std::numeric_limits<int>::max(), 0);
}

int main(int argc, char* argv[])
{
	const auto node7 = std::make_shared<Node>(7);
	const auto node6 = std::make_shared<Node>(6);
	const auto node5 = std::make_shared<Node>(5);
	const auto node4 = std::make_shared<Node>(4);
	const auto node3 = std::make_shared<Node>(3, node6, node7);
	const auto node2 = std::make_shared<Node>(2, node4, node5);
	const auto node1 = std::make_shared<Node>(1, node2, node3);

	std::cout << GetMinLevelSumOfTree(node1) << "\n";

	node1->value = 100;
	std::cout << GetMinLevelSumOfTree(node1) << "\n";

	node2->value = 200;
	std::cout << GetMinLevelSumOfTree(node1) << "\n";

	std::cin.get();

	return 0;
}