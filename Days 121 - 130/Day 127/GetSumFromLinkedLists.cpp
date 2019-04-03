#include <iostream>
#include <memory>

struct Node
{
	unsigned int value;

	std::shared_ptr<Node> next;

	explicit Node(const int value, const std::shared_ptr<Node>& next = nullptr) noexcept
		: value(value), next(next)
	{ }
};

unsigned int GetNumberFromLinkedList(const std::shared_ptr<Node>& root) noexcept
{
	unsigned int number = 0;
	std::shared_ptr<Node> currentNode = root;
	unsigned int multiplier = 1;

	while (currentNode != nullptr)
	{
		number += currentNode->value * multiplier;
		multiplier *= 10;
		currentNode = currentNode->next;
	}

	return number;
}

std::shared_ptr<Node> CreateLinkedListFromNumber(unsigned int number) noexcept
{
	std::shared_ptr<Node> currentNode;
	std::shared_ptr<Node> previousNode = nullptr;

	while (number > 0)
	{
		currentNode = std::make_shared<Node>(number % 10, previousNode);
		previousNode = currentNode;

		number /= 10;
	}

	std::shared_ptr<Node> nextNode = nullptr;
	previousNode = nullptr;

	while (currentNode != nullptr)
	{
		nextNode = currentNode->next;
		currentNode->next = previousNode;

		previousNode = currentNode;
		currentNode = nextNode;
	}

	return previousNode;
}

inline std::shared_ptr<Node> CreateSummationLinkedList(const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs) noexcept
{
	const unsigned int sum = GetNumberFromLinkedList(lhs) + GetNumberFromLinkedList(rhs);

	return CreateLinkedListFromNumber(sum);
}

int main(int argc, char* argv[])
{
	const auto node5 = std::make_shared<Node>(5);
	const auto node4 = std::make_shared<Node>(4, node5);
	const auto node3 = std::make_shared<Node>(3, node4);
	const auto node2 = std::make_shared<Node>(2, node3);
	const auto node1 = std::make_shared<Node>(1, node2);

	std::cout << GetNumberFromLinkedList(node1) << "\n";

	const auto node99B = std::make_shared<Node>(9);
	const auto node99A = std::make_shared<Node>(9, node99B);

	const auto node25B = std::make_shared<Node>(2);
	const auto node25A = std::make_shared<Node>(5, node25B);

	std::cout << GetNumberFromLinkedList(CreateSummationLinkedList(node99A, node25A)) << "\n";

	std::cin.get();

	return 0;
}