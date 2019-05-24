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

void RotateLinkedList(const std::shared_ptr<Node>& head, unsigned int rotationAmount) noexcept
{
	if (head == nullptr)
	{
		return;
	}

	// If the size of the list is known ahead of this function, this first loop can be skipped
	unsigned int size = 0;
	auto currentNode = head;
	
	while (currentNode != nullptr)
	{
		++size;
		currentNode = currentNode->next;
	}

	rotationAmount = size - (rotationAmount % size);
	currentNode = head;

	unsigned int index = 0;

	while (currentNode != nullptr)
	{
		if (index == rotationAmount - 1)
		{
			const auto newTail = currentNode;
			currentNode = currentNode->next;
			newTail->next = nullptr;
		}
		else if (index == size - 1)
		{
			const auto newHead = currentNode;
			currentNode = currentNode->next;
			newHead->next = head;
		}
		else
		{
			currentNode = currentNode->next;
		}
		
		++index;
	}
}

std::ostream& operator <<(std::ostream& outputStream, const std::shared_ptr<Node>& head) noexcept
{
	auto currentNode = head;

	while (currentNode != nullptr)
	{
		outputStream << currentNode->value << " ";
		currentNode = currentNode->next;
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	const auto nodeA4 = std::make_shared<Node>(5);
	const auto nodeA3 = std::make_shared<Node>(3, nodeA4);
	const auto nodeA2 = std::make_shared<Node>(7, nodeA3);
	const auto nodeA1 = std::make_shared<Node>(7, nodeA2);

	std::cout << "Before rotation at node 3: " << nodeA3 << "\n";
	RotateLinkedList(nodeA1, 2);
	std::cout << "After rotation at node 3:  " << nodeA3 << "\n";

	const auto nodeB5 = std::make_shared<Node>(5);
	const auto nodeB4 = std::make_shared<Node>(4, nodeB5);
	const auto nodeB3 = std::make_shared<Node>(3, nodeB4);
	const auto nodeB2 = std::make_shared<Node>(2, nodeB3);
	const auto nodeB1 = std::make_shared<Node>(1, nodeB2);

	std::cout << "Before rotation at node 3: " << nodeB3 << "\n";
	RotateLinkedList(nodeB1, 3);
	std::cout << "After rotation at node 3:  " << nodeB3 << "\n";

	std::cin.get();

	return 0;
}