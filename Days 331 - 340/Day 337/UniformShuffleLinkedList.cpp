#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <random>
#include <vector>

struct Node
{
	int value;

	std::shared_ptr<Node> next;

	explicit Node(const int value, const std::shared_ptr<Node>& next = nullptr)
		: value(value), next(next)
	{ }
};

std::shared_ptr<Node> CreateLinkedListFromVector(const std::vector<int>& numbers)
{
	std::shared_ptr<Node> nextNode = nullptr;

	for (auto rIt = std::crbegin(numbers); rIt != std::crend(numbers); ++rIt)
	{
		const auto currentNode = std::make_shared<Node>(*rIt, nextNode);
		nextNode = currentNode;
	}

	return nextNode;
}

std::vector<int> CreateVectorFromLinkedList(const std::shared_ptr<Node>& head)
{
	std::vector<int> numbers;
	auto currentNode = head;

	while (currentNode != nullptr)
	{
		numbers.push_back(currentNode->value);
		currentNode = currentNode->next;
	}

	return numbers;
}

std::shared_ptr<Node> UniformShuffleLinkedList(const std::shared_ptr<Node>& head)
{
	auto listVector = CreateVectorFromLinkedList(head);
	std::shuffle(std::begin(listVector), std::end(listVector), std::mt19937(std::random_device()()));

	return CreateLinkedListFromVector(listVector);
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
	const auto node10 = std::make_shared<Node>(10);
	const auto node9 = std::make_shared<Node>(9, node10);
	const auto node8 = std::make_shared<Node>(8, node9);
	const auto node7 = std::make_shared<Node>(7, node8);
	const auto node6 = std::make_shared<Node>(6, node7);
	const auto node5 = std::make_shared<Node>(5, node6);
	const auto node4 = std::make_shared<Node>(4, node5);
	const auto node3 = std::make_shared<Node>(3, node4);
	const auto node2 = std::make_shared<Node>(2, node3);
	const auto node1 = std::make_shared<Node>(1, node2);

	std::cout << node1 << "\n";
	std::cout << UniformShuffleLinkedList(node1) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}