#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>

struct Node
{
	int value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(const int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr)
		: value(value), left(left), right(right)
	{ }
};

std::shared_ptr<Node> CreateCartesianTreeHelper(const std::initializer_list<int>& numbers, const std::shared_ptr<Node>& root, const std::shared_ptr<Node>& previousNode)
{
	if (numbers.size() == 0)
	{
		return root;
	}

	const auto currentNode = std::make_shared<Node>(*std::cbegin(numbers));
	const std::initializer_list<int> successiveNumbers(std::cbegin(numbers) + 1, std::cend(numbers));

	if (previousNode == nullptr)
	{
		return CreateCartesianTreeHelper(successiveNumbers, currentNode, currentNode);
	}

	if (previousNode->value > currentNode->value)
	{
		currentNode->left = previousNode;

		return CreateCartesianTreeHelper(successiveNumbers, currentNode, currentNode);
	}

	previousNode->right = currentNode;

	return CreateCartesianTreeHelper(successiveNumbers, previousNode, previousNode);
}

inline std::shared_ptr<Node>CreateCartesianTree(const std::initializer_list<int>& numbers)
{
	return CreateCartesianTreeHelper(numbers, nullptr, nullptr);
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

int main(const int argc, const char* const argv[])
{
	std::cout << CreateCartesianTree({ 3, 2, 6, 1, 9 }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}