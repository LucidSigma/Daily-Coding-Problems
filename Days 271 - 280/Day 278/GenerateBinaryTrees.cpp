#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>

template <typename T = size_t, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
struct Node
{
	T value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(const T value, const std::shared_ptr<Node<T>>& left = nullptr, const std::shared_ptr<Node<T>>& right = nullptr)
		: value(value), left(left), right(right)
	{ }
};

template <typename T = size_t, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
std::vector<std::shared_ptr<Node<T>>> GenerateBinaryTreesHelper(std::vector<std::shared_ptr<Node<T>>> nodes)
{
	if (nodes.empty() || nodes.size() == 1)
	{
		return nodes;
	}

	using TreeVector = std::vector<std::shared_ptr<Node<T>>>;

	TreeVector binaryTrees;

	for (size_t i = 0; i < nodes.size(); ++i)
	{
		const TreeVector leftNodes = i > 0 ? GenerateBinaryTreesHelper(TreeVector(std::cbegin(nodes), std::cbegin(nodes) + i)) : TreeVector{ };
		const TreeVector rightNodes = i < nodes.size() - 1 ? GenerateBinaryTreesHelper(TreeVector(std::cbegin(nodes) + i + 1, std::cend(nodes))) : TreeVector{ };

		for (const auto& leftNode : leftNodes)
		{
			for (const auto& rightNode : rightNodes)
			{
				nodes[i]->left = leftNode;
				nodes[i]->right = rightNode;

				binaryTrees.push_back(nodes[i]);
			}
		}
	}

	return binaryTrees;
}

template <typename T = size_t, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
std::vector<std::shared_ptr<Node<T>>> GenerateBinaryTrees(const unsigned int count)
{
	std::vector<std::shared_ptr<Node<T>>> nodes(count, nullptr);

	for (size_t i = 0; i < nodes.size(); ++i)
	{
		nodes[i] = std::make_shared<Node<T>>(i);
	}

	return GenerateBinaryTreesHelper(nodes);
}

template <typename T = size_t, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
std::ostream& operator <<(std::ostream& outputStream, const std::shared_ptr<Node<T>>& node)
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

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << "\n";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << GenerateBinaryTrees(4) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}