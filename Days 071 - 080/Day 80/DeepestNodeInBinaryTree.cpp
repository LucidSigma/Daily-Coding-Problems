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

auto FindDeepestNodeHelper(std::shared_ptr<Node> root, unsigned int depth) noexcept -> std::pair<decltype(root), decltype(depth)>
{
	if (root->left == nullptr && root->right == nullptr)
	{
		return { root, depth };
	}

	unsigned int leftDepth = depth;
	unsigned int rightDepth = depth;

	std::shared_ptr<Node> leftDeepest;
	std::shared_ptr<Node> rightDeepest;

	if (root->left != nullptr)
	{
		auto left = FindDeepestNodeHelper(root->left, depth + 1);

		leftDeepest = left.first;
		leftDepth = left.second;
	}

	if (root->right != nullptr)
	{
		auto right = FindDeepestNodeHelper(root->right, depth + 1);

		rightDeepest = right.first;
		rightDepth = right.second;
	}

	return leftDepth > rightDepth ? std::make_pair(leftDeepest, leftDepth) : std::make_pair(rightDeepest, rightDepth);
}

inline auto FindDeepestNode(std::shared_ptr<Node> root) noexcept -> decltype(root)
{
	return FindDeepestNodeHelper(root, 0).first;
}

int main(int argc, char* argv[])
{
	auto n4 = std::make_shared<Node>('d');
	auto n3 = std::make_shared<Node>('c');
	auto n2 = std::make_shared<Node>('b', n4);
	auto n1 = std::make_shared<Node>('a', n2, n3);

	std::cout << FindDeepestNode(n1)->value << "\n";

	std::cin.get();

	return 0;
}