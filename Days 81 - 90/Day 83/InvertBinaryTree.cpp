#include <iostream>
#include <memory>
#include <utility>

struct Node
{
	char value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(char value, std::shared_ptr<Node> left = nullptr, std::shared_ptr<Node> right = nullptr) noexcept
		: value(value), left(left), right(right)
	{ }
};

void InvertBinaryTree(std::shared_ptr<Node> node) noexcept
{
	if (node == nullptr)
	{
		return;
	}

	std::swap(node->left, node->right);

	InvertBinaryTree(node->left);
	InvertBinaryTree(node->right);
}

void PrintBinaryTree(std::shared_ptr<Node> node)
{
	if (node == nullptr)
	{
		std::cout << "- ";

		return;
	}

	std::cout << node->value << " ";

	PrintBinaryTree(node->left);
	PrintBinaryTree(node->right);
}

int main(int argc, char* argv[])
{
	auto f = std::make_shared<Node>('f');
	auto e = std::make_shared<Node>('e');
	auto d = std::make_shared<Node>('d');
	auto c = std::make_shared<Node>('c', f);
	auto b = std::make_shared<Node>('b', d, e);
	auto a = std::make_shared<Node>('a', b, c);
	
	std::cout << "Before inversion:\n";
	PrintBinaryTree(a);
	
	InvertBinaryTree(a);
	
	std::cout << "\nAfter inversion:\n";
	PrintBinaryTree(a);
	
	std::cout << "\n";

	std::cin.get();

	return 0;
}