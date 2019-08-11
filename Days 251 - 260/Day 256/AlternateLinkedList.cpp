#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

struct Node
{
	int value;
	std::shared_ptr<Node> next;

	explicit Node(const int value, const std::shared_ptr<Node>& next = nullptr)
		: value(value), next(next)
	{ }
};

std::vector<int> LinkedListToVector(const std::shared_ptr<Node>& head)
{
	std::vector<int> values;
	auto currentNode = head;

	while (currentNode != nullptr)
	{
		values.push_back(currentNode->value);
		currentNode = currentNode->next;
	}

	return values;
}

std::shared_ptr<Node> VectorToLinkedList(const std::vector<int>& values)
{
	std::shared_ptr<Node> nextNode = nullptr;

	for (auto rIt = std::crbegin(values); rIt != std::crend(values); ++rIt)
	{
		const auto currentNode = std::make_shared<Node>(*rIt, nextNode);
		nextNode = currentNode;
	}

	return nextNode;
}

std::shared_ptr<Node> AlternateLinkedList(const std::shared_ptr<Node>& head)
{
	if (head == nullptr)
	{
		return nullptr;
	}
	else if (head->next == nullptr)
	{
		return head;
	}

	auto values = LinkedListToVector(head);
	std::sort(std::begin(values), std::end(values));

	for (size_t i = 1; i < values.size() - 1; i += 2)
	{
		std::swap(values[i], values[i + 1]);
	}

	return VectorToLinkedList(values);
}

std::ostream& operator <<(std::ostream& outputStream, const std::shared_ptr<Node>& node)
{
	auto currentNode = node;

	while (currentNode != nullptr)
	{
		outputStream << currentNode->value << " ";
		currentNode = currentNode->next;
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	const auto list = VectorToLinkedList({ 1, 2, 3, 4, 5 });

	std::cout << list << "\n";
	std::cout << AlternateLinkedList(list) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}