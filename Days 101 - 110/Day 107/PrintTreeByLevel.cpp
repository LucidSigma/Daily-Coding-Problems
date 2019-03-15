#include <iostream>
#include <memory>
#include <queue>

struct Node
{
	int value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr) noexcept
		: value(value), left(left), right(right)
	{ }
};

void PrintTreeByLevel(const std::shared_ptr<Node>& root) noexcept
{
	if (root == nullptr)
	{
		return;
	}

	std::queue<std::shared_ptr<Node>> nodeQueue;
	nodeQueue.push(root);

	while (!nodeQueue.empty())
	{
		unsigned int nodeCount = nodeQueue.size();

		while (nodeCount > 0)
		{
			std::shared_ptr<Node> currentNode = nodeQueue.front();

			std::cout << currentNode->value << " ";

			nodeQueue.pop();

			if (currentNode->left != nullptr)
			{
				nodeQueue.push(currentNode->left);
			}

			if (currentNode->right != nullptr)
			{
				nodeQueue.push(currentNode->right);
			}

			nodeCount--;
		}

		std::cout << "\n";
	}
}

int main(int argc, char* argv[])
{
	const auto n5 = std::make_shared<Node>(5);
	const auto n4 = std::make_shared<Node>(4);
	const auto n3 = std::make_shared<Node>(3, n4, n5);
	const auto n2 = std::make_shared<Node>(2);
	const auto n1 = std::make_shared<Node>(1, n2, n3);

	PrintTreeByLevel(n1);

	std::cin.get();

	return 0;
}