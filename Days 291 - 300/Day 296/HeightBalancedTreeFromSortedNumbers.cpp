#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

struct Node
{
	int value;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(const int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr)
		: value(value), left(left), right(right)
	{ }
};

std::shared_ptr<Node> CreateHeightBalancedTree(const std::vector<int>& sortedNumbers)
{
	if (sortedNumbers.empty())
	{
		return nullptr;
	}

	const size_t midpoint = sortedNumbers.size() / 2;

	const auto leftNode = CreateHeightBalancedTree(std::vector<int>(std::cbegin(sortedNumbers), std::cbegin(sortedNumbers) + midpoint));
	const auto rightNode = CreateHeightBalancedTree(std::vector<int>(std::cbegin(sortedNumbers) + midpoint + 1, std::cend(sortedNumbers)));
	const auto node = std::make_shared<Node>(sortedNumbers[midpoint], leftNode, rightNode);

	return node;
}

std::ostream& operator <<(std::ostream& outputStream, const std::shared_ptr<Node>& node)
{
	if (node == nullptr)
	{
		outputStream << "-";
	}
	else
	{
		outputStream << node->value << " " << node->left << " " << node->right;
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << CreateHeightBalancedTree({ 1, 2, 4, 6, 8, 9 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}