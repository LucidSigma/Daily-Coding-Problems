#include <algorithm>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <unordered_map>
#include <vector>

struct Node
{
	int value;
	std::vector<std::shared_ptr<Node>> children;

	explicit Node(const int value, const std::initializer_list<std::shared_ptr<Node>>& children = { }) noexcept
		: value(value), children(children)
	{ }
};

void UpdateNodeLevels(const std::shared_ptr<Node>& root, std::unordered_map<unsigned int, std::vector<int>>& nodeLevels, const unsigned int currentLevel) noexcept
{
	if (nodeLevels.find(currentLevel) == std::cend(nodeLevels))
	{
		nodeLevels[currentLevel] = { };
	}

	nodeLevels[currentLevel].push_back(root->value);

	for (const auto& child : root->children)
	{
		UpdateNodeLevels(child, nodeLevels, currentLevel + 1);
	}
}

bool IsSymmetric(const std::shared_ptr<Node>& root) noexcept
{
	std::unordered_map<unsigned int, std::vector<int>> nodeLevels;
	UpdateNodeLevels(root, nodeLevels, 0);

	for (const auto& [level, levels] : nodeLevels)
	{
		auto reversedLevels = levels;
		std::reverse(std::begin(reversedLevels), std::end(reversedLevels));

		if (levels != reversedLevels)
		{
			return false;
		}
	}

	return true;
}

int main(int argc, char* argv[])
{
	const auto leftLeft = std::make_shared<Node>(9);
	const auto rightRight = std::make_shared<Node>(9);

	const auto left = std::make_shared<Node>(3, std::initializer_list{ leftLeft });
	const auto middle = std::make_shared<Node>(5);
	const auto right = std::make_shared<Node>(3, std::initializer_list{ rightRight });

	const auto root = std::make_shared<Node>(4, std::initializer_list{ left, middle, right });

	std::cout << std::boolalpha;
	std::cout << IsSymmetric(root) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}