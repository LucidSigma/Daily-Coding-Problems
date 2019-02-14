#include <functional>
#include <iostream>
#include <queue>
#include <type_traits>
#include <vector>

// SMART POINTERS

struct Node
{
	int value;
	Node* next;

	explicit Node(int value, Node* next = nullptr) noexcept
		: value(value), next(next)
	{ }
};

struct NodePointerComparison
{
	bool operator ()(Node* left, Node* right) const noexcept
	{
		return left->value < right->value;
	}
};

template <typename... Args, typename = std::enable_if_t<(... && std::is_convertible_v<Args, int>)>>
Node* CreateList(Args... values) noexcept
{
	Node* nextNode = nullptr;
	Node* node = nullptr;

	(..., [&nextNode, &node, values]()
	{
		node = new Node(values, nextNode);
		nextNode = node;
	}());

	return nextNode;
}

Node* MergeLists(const std::vector<Node*>& lists) noexcept
{
	Node* head = new Node(0);
	Node* tail = head;
	std::priority_queue<Node*, std::vector<Node*>, NodePointerComparison> candidates;
	unsigned int counter = 0;

	for (Node* list : lists)
	{
		candidates.push(list);
		counter++;
	}

	while (!candidates.empty())
	{
		Node* newNode = candidates.top();
		candidates.pop();

		if (newNode->next != nullptr)
		{
			candidates.push(newNode->next);
			counter++;
		}

		tail->next = newNode;
		tail = newNode;
	}

	return head->next;
}

void PrintList(Node* head)
{
	Node* currentNode = head;

	while (currentNode != nullptr)
	{
		std::cout << currentNode->value << " ";
		currentNode = currentNode->next;
	}

	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	std::vector<Node*> lists { CreateList(5, 4, 7, 3), CreateList(8, 6, 2, 0, 2, 7, 5), CreateList(7, 1, 4, 0, 3) };
	PrintList(MergeLists(lists));

	std::cin.get();

	return 0;
}