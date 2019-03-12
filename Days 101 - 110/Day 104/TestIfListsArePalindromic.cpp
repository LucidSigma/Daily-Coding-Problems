#include <iostream>
#include <memory>
#include <utility>

struct Node
{
	int value;
	std::shared_ptr<Node> next;
	
	explicit Node(int value, const std::shared_ptr<Node>& next = nullptr)
		: value(value), next(next)
	{ }
};

struct DoubleNode
{
	int value;
	std::shared_ptr<DoubleNode> next;
	std::shared_ptr<DoubleNode> previous;

	explicit DoubleNode(int value, const std::shared_ptr<DoubleNode>& next = nullptr, const std::shared_ptr<DoubleNode>& previous = nullptr)
		: value(value), next(next), previous(previous)
	{ }
};

std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> ReverseSinglyLinkedList(const std::shared_ptr<Node>& head) noexcept
{
	if (head->next != nullptr)
	{
		auto newHead = std::make_shared<Node>(head->value);

		return { newHead, newHead };
	}

	auto[reverseHead, reverseTail] = ReverseSinglyLinkedList(head->next);
	reverseTail->next = std::make_shared<Node>(head->value);

	return { reverseHead, reverseTail->next };
}

bool IsSinglyLinkedListPalindrome(const std::shared_ptr<Node>& head) noexcept
{
	if (head == nullptr)
	{
		return true;
	}

	auto currentNode = head;
	auto currentReverseNode = ReverseSinglyLinkedList(head).first;

	while (currentNode != nullptr)
	{
		if (currentNode->value != currentReverseNode->value)
		{
			return false;
		}

		currentNode = currentNode->next;
		currentReverseNode = currentReverseNode->next;
	}

	return true;
}

bool IsDoublyLinkedListPalindrome(const std::shared_ptr<DoubleNode>& head) noexcept
{
	auto reverseNode = head;

	while (reverseNode->next != nullptr)
	{
		reverseNode = reverseNode->next;
	}

	auto currentNode = head;

	while (currentNode != nullptr)
	{
		if (currentNode->value != reverseNode->value)
		{
			return false;
		}

		currentNode = currentNode->next;
		reverseNode = reverseNode->previous;
	}

	return true;
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;

	auto nodeA0 = std::make_shared<DoubleNode>(1, nullptr);
	auto nodeA1 = std::make_shared<DoubleNode>(4, nodeA0);
	auto nodeA2 = std::make_shared<DoubleNode>(3, nodeA1);
	auto nodeA3 = std::make_shared<DoubleNode>(4, nodeA2);
	auto nodeA4 = std::make_shared<DoubleNode>(1, nodeA3);

	nodeA0->previous = nodeA1;
	nodeA1->previous = nodeA2;
	nodeA2->previous = nodeA3;
	nodeA3->previous = nodeA4;

	std::cout << IsDoublyLinkedListPalindrome(nodeA4) << "\n";

	auto nodeB0 = std::make_shared<DoubleNode>(4);
	auto nodeB1 = std::make_shared<DoubleNode>(1, nodeB0);

	std::cout << IsDoublyLinkedListPalindrome(nodeB1) << "\n";

	auto singlyNodeA0 = std::make_shared<Node>(1);
	auto singlyNodeA1 = std::make_shared<Node>(4, singlyNodeA0);
	auto singlyNodeA2 = std::make_shared<Node>(3, singlyNodeA1);
	auto singlyNodeA3 = std::make_shared<Node>(4, singlyNodeA2);
	auto singlyNodeA4 = std::make_shared<Node>(1, singlyNodeA3);

	std::cout << IsSinglyLinkedListPalindrome(singlyNodeA4) << "\n";
	
	auto singlyNodeB0 = std::make_shared<Node>(4);
	auto singlyNodeB1 = std::make_shared<Node>(1, singlyNodeB0);

	std::cout << IsSinglyLinkedListPalindrome(singlyNodeB1) << "\n";

	std::cin.get();

	return 0;
}