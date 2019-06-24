#include <iostream>
#include <memory>
#include <type_traits>

struct Node
{
	int value;
	std::shared_ptr<Node> next;

	explicit Node(const int value, const std::shared_ptr<Node>& next = nullptr) noexcept
		: value(value), next(next)
	{ }
};

template <typename... Args, typename = std::enable_if_t<(... && std::is_convertible_v<Args, int>)>>
std::shared_ptr<Node> CreateLinkedList(Args&&... values) noexcept
{
	std::shared_ptr<Node> nextNode = nullptr;
	std::shared_ptr<Node> currentNode = nullptr;

	([&nextNode, &currentNode, values]()
	{
		currentNode = std::make_shared<Node>(values, nextNode);
		nextNode = currentNode;
	}(), ...);

	return nextNode;
}

std::shared_ptr<Node> PartitionLinkedList(std::shared_ptr<Node>& list, const unsigned int k) noexcept
{
	std::shared_ptr<Node> headNode = list;
	std::shared_ptr<Node> previousNode = headNode;
	std::shared_ptr<Node> currentNode = headNode->next;

	while (currentNode != nullptr)
	{
		if (currentNode->value < k)
		{
			previousNode->next = currentNode->next;
			currentNode->next = headNode;
			headNode = currentNode;
			currentNode = previousNode->next;
		}
		else
		{
			previousNode = currentNode;
			currentNode = currentNode->next;
		}
	}

	return headNode;
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
	auto list = CreateLinkedList(5, 1, 8, 0, 3);
	std::cout << "Before partition: " << list << "\n";

	const auto partitionedList = PartitionLinkedList(list, 3);
	std::cout << " After partition: " << partitionedList << "\n";

	std::cin.get();

	return 0;
}