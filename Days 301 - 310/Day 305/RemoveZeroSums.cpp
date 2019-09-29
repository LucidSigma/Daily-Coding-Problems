#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <unordered_map>

struct Node
{
	int value;
	std::shared_ptr<Node> next;
	
	int cumulativeSum = 0;

	explicit Node(const int value, const std::shared_ptr<Node>& next = nullptr)
		: value(value), next(next)
	{ }
};

void SetCumulativeSums(const std::shared_ptr<Node>& head)
{
	auto currentNode = head;
	int cumulativeSum = 0;

	while (currentNode != nullptr)
	{
		currentNode->cumulativeSum = currentNode->value + cumulativeSum;
		cumulativeSum = currentNode->cumulativeSum;

		currentNode = currentNode->next;
	}
}

std::shared_ptr<Node> RemoveZeroSums(const std::shared_ptr<Node>& head)
{
	SetCumulativeSums(head);
	std::shared_ptr<Node> newList = std::make_shared<Node>(0, head);

	std::unordered_map<int, std::shared_ptr<Node>> seenSums;
	std::shared_ptr<Node> currentNode = newList;

	while (currentNode != nullptr)
	{
		if (seenSums.find(currentNode->cumulativeSum) != std::cend(seenSums))
		{
			seenSums[currentNode->cumulativeSum]->next = currentNode->next;
		}

		seenSums[currentNode->cumulativeSum] = currentNode;
		currentNode = currentNode->next;
	}

	return newList->next;
}

std::ostream& operator <<(std::ostream& outputStream, const std::shared_ptr<Node>& head)
{
	auto currentNode = head;

	while (currentNode != nullptr)
	{
		outputStream << currentNode->value << " ";
		
		currentNode = currentNode->next;
	}

	return outputStream;
}

int main(const int argc, const char* const argv[])
{
	const auto node6 = std::make_shared<Node>(6);
	const auto nodeN6 = std::make_shared<Node>(-6, node6);
	const auto node5 = std::make_shared<Node>(5, nodeN6);
	const auto nodeN7 = std::make_shared<Node>(-7, node5);
	const auto node4 = std::make_shared<Node>(4, nodeN7);
	const auto node3 = std::make_shared<Node>(3, node4);
	
	std::cout << RemoveZeroSums(node3) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}