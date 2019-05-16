#include <iostream>
#include <memory>
#include <vector>

struct Node
{
	int value;
	std::shared_ptr<Node> next;

	explicit Node(const int value, const std::shared_ptr<Node>& next = nullptr) noexcept
		: value{ value }, next{ next }
	{ }
};

std::shared_ptr<Node> MergeSortedLinkedLists(const std::shared_ptr<Node>& listA, const std::shared_ptr<Node>& listB) noexcept
{
	std::shared_ptr<Node> head{ std::make_shared<Node>(std::numeric_limits<int>::min()) };
	std::shared_ptr<Node> currentNode{ head };

	std::shared_ptr<Node> nodeA{ listA };
	std::shared_ptr<Node> nodeB{ listB };

	while (nodeA != nullptr && nodeB != nullptr)
	{
		std::shared_ptr<Node> tempNode{ nodeA->value < nodeB->value ? nodeA : nodeB };

		if (nodeA->value < nodeB->value)
		{
			nodeA = nodeA->next;
		}
		else
		{
			nodeB = nodeB->next;
		}

		tempNode->next = nullptr;
		currentNode->next = tempNode;
		currentNode = currentNode->next;
	}

	if (nodeA != nullptr)
	{
		currentNode->next = nodeA;
	}

	if (nodeB != nullptr)
	{
		currentNode->next = nodeB;
	}

	return head->next;
}

std::shared_ptr<Node> SortLinkedListHelper(const std::shared_ptr<Node>& linkedList, const unsigned int nodeCount) noexcept
{
	if (nodeCount == 1)
	{
		return linkedList;
	}

	const unsigned int midPoint = nodeCount / 2;
	std::shared_ptr<Node> rightListHead{ linkedList };
	std::shared_ptr<Node> leftListTail{ nullptr };

	for (unsigned int i{ 0 }; i < midPoint; ++i)
	{
		leftListTail = rightListHead;
		rightListHead = rightListHead->next;
	}

	leftListTail->next = nullptr;

	const std::shared_ptr<Node> sortedLeftList{ SortLinkedListHelper(linkedList, midPoint) };
	const std::shared_ptr<Node> sortedRightList{ SortLinkedListHelper(rightListHead, nodeCount - midPoint) };

	return MergeSortedLinkedLists(sortedLeftList, sortedRightList);
}

std::shared_ptr<Node> SortLinkedList(const std::shared_ptr<Node>& linkedList) noexcept
{
	unsigned int nodeCount{ 0 };
	auto currentNode{ linkedList };

	while (currentNode != nullptr)
	{
		++nodeCount;
		currentNode = currentNode->next;
	}

	return SortLinkedListHelper(linkedList, nodeCount);
}

std::ostream& operator <<(std::ostream& outputStream, const std::shared_ptr<Node>& linkedList) noexcept
{
	auto currentNode{ linkedList };

	outputStream << "[ ";

	while (currentNode != nullptr)
	{
		outputStream << currentNode->value << " ";

		currentNode = currentNode->next;
	}

	outputStream << "]";

	return outputStream;
}

int main(int argc, char* argv[])
{
	const auto node99{ std::make_shared<Node>(99) };
	const auto nodeN3{ std::make_shared<Node>(-3, node99) };
	const auto node1{ std::make_shared<Node>(1, nodeN3) };
	const auto node4{ std::make_shared<Node>(4, node1) };

	std::cout << "Before sorting: " << node4 << "\n";

	const auto sortedList{ SortLinkedList(node4) };

	std::cout << " After sorting: " << sortedList << "\n";

	std::cin.get();

	return 0;
}