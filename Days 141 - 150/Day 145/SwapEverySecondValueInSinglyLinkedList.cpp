#include <algorithm>
#include <iostream>
#include <memory>

struct Node
{
	int value;
	std::shared_ptr<Node> next;

	explicit Node(const int value, const std::shared_ptr<Node>& next = nullptr) noexcept
		: value(value), next(next)
	{ }
};

std::shared_ptr<Node> SwapEverySeceondNode(const std::shared_ptr<Node>& root) noexcept
{
	auto currentNode = root;
	const auto newHead = currentNode;
	decltype(currentNode) nextNode;

	if (currentNode->next == nullptr)
	{
		return currentNode;
	}
	else
	{
		nextNode = currentNode->next;
	}

	while (currentNode != nullptr)
	{
		std::swap(currentNode->value, nextNode->value);

		currentNode = nextNode->next;

		if (currentNode != nullptr)
		{
			nextNode = currentNode->next;
		}
	}

	return newHead;
}

void PrintSinglyLinkedList(const std::shared_ptr<Node>& root) noexcept
{
	auto currentNode = root;

	while (currentNode != nullptr)
	{
		std::cout << currentNode->value << " ";

		currentNode = currentNode->next;
	}

	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	const auto n4 = std::make_shared<Node>(4);
	const auto n3 = std::make_shared<Node>(3, n4);
	const auto n2 = std::make_shared<Node>(2, n3);
	const auto n1 = std::make_shared<Node>(1, n2);

	PrintSinglyLinkedList(n1);

	const auto swappedList = SwapEverySeceondNode(n1);
	PrintSinglyLinkedList(swappedList);

	std::cin.get();

	return 0;
}