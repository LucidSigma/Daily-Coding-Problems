#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <unordered_map>

struct Node
{
	int value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(const int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr)
		: value(value), left(left), right(right)
	{ }
};

void GetBoustrophedonOrderHelper(const std::shared_ptr<Node>& node, const unsigned int currentLevel, std::unordered_map<unsigned int, std::vector<int>>& levelValues)
{
	if (node == nullptr)
	{
		return;
	}
	
	if (levelValues.find(currentLevel) == std::cend(levelValues))
	{
		levelValues[currentLevel] = { };
	}

	levelValues[currentLevel].push_back(node->value);

	GetBoustrophedonOrderHelper(node->left, currentLevel + 1, levelValues);
	GetBoustrophedonOrderHelper(node->right, currentLevel + 1, levelValues);
}

std::vector<int> GetBoustrophedonOrder(const std::shared_ptr<Node>& root)
{
	std::unordered_map<unsigned int, std::vector<int>> levelValues;
	GetBoustrophedonOrderHelper(root, 0, levelValues);

	std::vector<int> boustrophedonOrder;

	for (unsigned int i = 0; i < levelValues.size(); ++i)
	{
		if (i % 2 != 0)
		{
			std::reverse(std::begin(levelValues[i]), std::end(levelValues[i]));
		}

		boustrophedonOrder.insert(std::cend(boustrophedonOrder), std::cbegin(levelValues[i]), std::cend(levelValues[i]));
	}

	return boustrophedonOrder;
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
	const auto leftLeft = std::make_shared<Node>(4);
	const auto leftRight = std::make_shared<Node>(5);
	const auto rightLeft = std::make_shared<Node>(6);
	const auto rightRight = std::make_shared<Node>(7);

	const auto left = std::make_shared<Node>(2, leftLeft, leftRight);
	const auto right = std::make_shared<Node>(3, rightLeft, rightRight);

	const auto root = std::make_shared<Node>(1, left, right);

	std::cout << GetBoustrophedonOrder(root) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}