#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

struct Node
{
	int value;
	std::vector<std::shared_ptr<Node>> children;

	inline explicit Node(const int value, const std::vector<std::shared_ptr<Node>>& children = { })
		: value(value), children(children)
	{ }
};

unsigned int TreeSize(const std::shared_ptr<Node>& root)
{
	unsigned int nodeCount = 1;

	if (!root->children.empty())
	{
		for (const auto& childNode : root->children)
		{
			nodeCount += TreeSize(childNode);
		}
	}

	return nodeCount;
}

std::vector<std::shared_ptr<Node>> RemoveEdge(const std::shared_ptr<Node>& node)
{
	std::vector<std::shared_ptr<Node>> newTree;

	for (const auto& childNode : node->children)
	{
		if (TreeSize(childNode) % 2 == 0)
		{
			std::vector<std::shared_ptr<Node>> newChildren;

			for (const auto& child : node->children)
			{
				if (child == childNode)
				{
					continue;
				}

				newChildren.push_back(child);
			}

			node->children = newChildren;

			return { node, childNode };
		}
		else
		{
			const auto successiveChildren = RemoveEdge(childNode);

			newTree.insert(std::cend(newTree), std::cbegin(successiveChildren), std::cend(successiveChildren));
		}
	}

	return newTree;
}

unsigned int GetMaxCutsForEvenSubtreesHelper(const std::vector<std::shared_ptr<Node>>& nodes)
{
	std::vector<std::shared_ptr<Node>> newTree;
	
	for (const auto& node : nodes)
	{
		newTree = RemoveEdge(node);
	}

	if (newTree.size() == nodes.size())
	{
		return nodes.size();
	}

	return GetMaxCutsForEvenSubtreesHelper(newTree);
}

inline unsigned int GetMaxCutsForEvenSubtrees(const std::shared_ptr<Node>& root)
{
	return GetMaxCutsForEvenSubtreesHelper({ root });
}

int main(const int argc, const char* const argv[])
{
	const auto node8 = std::make_shared<Node>(8);
	const auto node7 = std::make_shared<Node>(7);
	const auto node6 = std::make_shared<Node>(6);

	const auto node5 = std::make_shared<Node>(5);
	const auto node4 = std::make_shared<Node>(4, std::vector<std::shared_ptr<Node>>{ node6, node7, node8 });

	const auto node3 = std::make_shared<Node>(3, std::vector<std::shared_ptr<Node>>{ node4, node5 });
	const auto node2 = std::make_shared<Node>(2);

	const auto node1 = std::make_shared<Node>(1, std::vector<std::shared_ptr<Node>>{ node2, node3 });

	std::cout << GetMaxCutsForEvenSubtrees(node1) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}