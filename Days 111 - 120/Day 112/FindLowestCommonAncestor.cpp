#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>

struct Node
{
	char value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	std::shared_ptr<Node> parent = nullptr;

	explicit Node(char value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr) noexcept
		: value(value), left(left), right(right)
	{ }
};

unsigned int GetNodeDepth(const std::shared_ptr<Node>& node) noexcept
{
	if (node == nullptr)
	{
		return 0;
	}

	return GetNodeDepth(node->parent) + 1;
}

std::shared_ptr<Node> GetLowestCommonAncestor(const std::shared_ptr<Node>& nodeA, const std::shared_ptr<Node>& nodeB) noexcept
{
	if (nodeA == nullptr || nodeB == nullptr)
	{
		return nullptr;
	}

	const unsigned int nodeADepth = GetNodeDepth(nodeA);
	const unsigned int nodeBDepth = GetNodeDepth(nodeB);

	const auto[minDepth, maxDepth] = std::minmax(nodeADepth, nodeBDepth);
	auto[deeperNode, shallowerNode] = nodeADepth > nodeBDepth ? std::make_pair(nodeA, nodeB) : std::make_pair(nodeB, nodeA);

	for (unsigned int i = 0; i < maxDepth - minDepth; i++)
	{
		deeperNode = deeperNode->parent;
	}

	while (deeperNode != nullptr && shallowerNode != nullptr)
	{
		if (deeperNode == shallowerNode)
		{
			return deeperNode;
		}

		deeperNode = deeperNode->parent;
		shallowerNode = shallowerNode->parent;
	}

	return nullptr;
}

int main(int argc, char* argv[])
{
	const auto nodeG = std::make_shared<Node>('g');
	const auto nodeF = std::make_shared<Node>('f');
	const auto nodeE = std::make_shared<Node>('e');
	const auto nodeD = std::make_shared<Node>('d', nodeF, nodeG);

	nodeF->parent = nodeD;
	nodeG->parent = nodeD;

	const auto nodeC = std::make_shared<Node>('c', nodeD, nodeE);

	nodeD->parent = nodeC;
	nodeE->parent = nodeC;

	const auto nodeB = std::make_shared<Node>('b');
	const auto nodeA = std::make_shared<Node>('a', nodeB, nodeC);

	nodeB->parent = nodeA;
	nodeC->parent = nodeA;

	std::cout << GetLowestCommonAncestor(nodeB, nodeE)->value << "\n";
	std::cout << GetLowestCommonAncestor(nodeE, nodeF)->value << "\n";

	std::cin.get();

	return 0;
}