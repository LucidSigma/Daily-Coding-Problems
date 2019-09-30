#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <utility>
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

std::vector<int> FlattenTree(const std::shared_ptr<Node>& root)
{
	if (root == nullptr)
	{
		return { };
	}

	auto flattenedTree = FlattenTree(root->left);
	flattenedTree.push_back(root->value);

	const auto rightFlattenedTree = FlattenTree(root->right);
	flattenedTree.insert(std::cend(flattenedTree), std::cbegin(rightFlattenedTree), std::cend(rightFlattenedTree));

	return flattenedTree;
}

std::pair<std::optional<int>, std::optional<int>> GetFloorAndCeilingFromTree(const std::shared_ptr<Node>& root, const int value)
{
	auto flattenedTree = FlattenTree(root);
	std::sort(std::begin(flattenedTree), std::end(flattenedTree));

	const size_t index = *std::find(std::cbegin(flattenedTree), std::cend(flattenedTree), value);

	if (index == 0)
	{
		return { std::nullopt, flattenedTree.front() };
	}
	else if (index == flattenedTree.size())
	{
		return { flattenedTree.back(), std::nullopt };
	}
	else if (value == flattenedTree[index - 1])
	{
		return { value, value };
	}
	else
	{
		return { flattenedTree[index - 1], flattenedTree[index] };
	}
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::optional<T>& optional)
{
	if (optional.has_value())
	{
		outputStream << optional.value();
	}
	else
	{
		outputStream << "None";
	}

	return outputStream;
}

template <typename T, typename U>
inline std::ostream& operator <<(std::ostream& outputStream, const std::pair<T, U>& pair)
{
	outputStream << pair.first << ", " << pair.second;

	return outputStream;
}

int main(const int argc, const char* const argv[])
{
	const auto node7 = std::make_shared<Node>(7);
	const auto node6 = std::make_shared<Node>(6);
	const auto node5 = std::make_shared<Node>(5);
	const auto node4 = std::make_shared<Node>(4);

	const auto node3 = std::make_shared<Node>(3, node4, node5);
	const auto node2 = std::make_shared<Node>(2, node6, node7);

	const auto node1 = std::make_shared<Node>(1, node2, node3);

	std::cout << GetFloorAndCeilingFromTree(node1, 4) << "\n";
	std::cout << GetFloorAndCeilingFromTree(node1, 1) << "\n";
	std::cout << GetFloorAndCeilingFromTree(node1, 7) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}