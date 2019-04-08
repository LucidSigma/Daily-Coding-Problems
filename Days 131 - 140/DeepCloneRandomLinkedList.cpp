#include <iostream>
#include <limits>
#include <memory>
#include <unordered_map>

struct Node
{
	int value;

	std::shared_ptr<Node> next;
	std::shared_ptr<Node> randomNext;

	explicit Node(const int value, const std::shared_ptr<Node>& next = nullptr, const std::shared_ptr<Node>& randomNext = nullptr) noexcept
		: value(value), next(next), randomNext(randomNext)
	{ }
};

std::shared_ptr<Node> DeepCloneSinglyLinkedRandomList(const std::shared_ptr<Node>& root) noexcept
{
	std::unordered_map<std::shared_ptr<Node>, unsigned int> nodeToIndexMapping;
	std::unordered_map<unsigned int, unsigned int> indexToRandomIndexMapping;

	std::shared_ptr<Node> currentNode = root;
	unsigned int counter = 0;

	while (currentNode != nullptr)
	{
		nodeToIndexMapping[currentNode] = counter;

		currentNode = currentNode->next;
		counter++;
	}

	currentNode = root;
	counter = 0;

	while (currentNode != nullptr)
	{
		const unsigned int randomIndex = nodeToIndexMapping[currentNode->randomNext];
		indexToRandomIndexMapping[counter] = randomIndex;

		currentNode = currentNode->next;
		counter++;
	}

	auto newHead = std::make_shared<Node>(std::numeric_limits<int>::min());
	auto newTail = newHead;
	
	std::unordered_map<unsigned int, std::shared_ptr<Node>> indexToNodeMapping;
	
	currentNode = root;
	counter = 0;
	
	while (currentNode != nullptr)
	{
		const auto newNode = std::make_shared<Node>(currentNode->value);
		indexToNodeMapping[counter] = newNode;
		
		currentNode = currentNode->next;
		counter++;

		newTail->next = newNode;
		newTail = newNode;
	}

	currentNode = newHead->next;
	counter = 0;

	while (currentNode != nullptr)
	{
		const unsigned int randomIndex = indexToRandomIndexMapping[counter];
		currentNode->randomNext = indexToNodeMapping[randomIndex];

		currentNode = currentNode->next;
		counter++;
	}

	return newHead->next;
}

void PrintSinglyLinkedRandomList(const std::shared_ptr<Node>& root) noexcept
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
	auto n5 = std::make_shared<Node>(5);
	auto n4 = std::make_shared<Node>(4, n5);
	auto n3 = std::make_shared<Node>(3, n4);
	auto n2 = std::make_shared<Node>(2, n3);
	auto n1 = std::make_shared<Node>(1, n2);

	n5->randomNext = n1;
	n4->randomNext = n3;
	n3->randomNext = n3;
	n2->randomNext = n4;
	n1->randomNext = n2;

	const auto copiedList = DeepCloneSinglyLinkedRandomList(n1);

	std::cout << "ORIGINAL LIST: ";
	PrintSinglyLinkedRandomList(n1);

	std::cout << "COPIED LIST:   ";
	PrintSinglyLinkedRandomList(copiedList);

	std::cout << "\n";

	n1->value = 100;

	std::cout << "ORIGINAL LIST: ";
	PrintSinglyLinkedRandomList(n1);

	std::cout << "COPIED LIST:   ";
	PrintSinglyLinkedRandomList(copiedList);

	std::cin.get();

	return 0;
}