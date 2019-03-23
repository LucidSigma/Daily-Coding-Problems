#include <iostream>
#include <memory>

struct Node
{
	char value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(char value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr) noexcept
		: value(value), left(left), right(right)
	{ }
};

bool IsSubtree(const std::shared_ptr<Node>& s, const std::shared_ptr<Node>& t) noexcept
{
	if (s == nullptr || t == nullptr)
	{
		return s == t;
	}

	if (s->value == t->value)
	{
		return IsSubtree(s->left, t->left) || IsSubtree(s->right, t->right);
	}
	else
	{
		return false;
	}
}

bool ContainsSubtree(const std::shared_ptr<Node>& s, const std::shared_ptr<Node>& t) noexcept
{
	if (s == nullptr || t == nullptr)
	{
		return false;
	}

	if (s->value == t->value)
	{
		if (IsSubtree(s, t))
		{
			return true;
		}
	}

	return ContainsSubtree(s->left, t) || ContainsSubtree(s->right, t);
}

int main(int argc, char* argv[])
{
	const auto nodeG = std::make_shared<Node>('G');
	const auto nodeF = std::make_shared<Node>('F');
	const auto nodeE = std::make_shared<Node>('E');
	const auto nodeD = std::make_shared<Node>('D');
	const auto nodeC = std::make_shared<Node>('C', nodeF, nodeG);
	const auto nodeB = std::make_shared<Node>('B', nodeD, nodeE);
	const auto nodeA = std::make_shared<Node>('A', nodeB, nodeC);

	const auto nodeG2 = std::make_shared<Node>('G');
	const auto nodeF2 = std::make_shared<Node>('F');
	const auto nodeC2 = std::make_shared<Node>('C', nodeF2, nodeG2);

	const auto nodeH = std::make_shared<Node>('H');

	std::cout << std::boolalpha;
	std::cout << ContainsSubtree(nodeA, nodeC) << "\n";
	std::cout << ContainsSubtree(nodeA, nodeC2) << "\n";
	std::cout << ContainsSubtree(nodeA, nodeH) << "\n";
	std::cout << ContainsSubtree(nodeA, nodeA) << "\n";

	std::cin.get();

	return 0;
}