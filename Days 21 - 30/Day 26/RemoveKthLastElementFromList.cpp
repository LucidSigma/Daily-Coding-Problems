#include <iostream>

struct Node
{
	int value;
	Node* next;

	Node(int value, Node* next = nullptr)
		: value(value), next(next)
	{ }

	~Node() noexcept
	{
		if (next != nullptr)
		{
			delete next;			
		}
	}
};

void RemoveKthLastElementFromList(Node* head, int k) noexcept
{
	Node* front = head;
	Node* back = head;

	while (front != nullptr)
	{
		front = front->next;
		
		if (k < 0)
		{
			back = back->next;
		}

		k--;
	}

	if (k == 0)
	{
		head = head->next;
	}
	else
	{
		if (back->next != nullptr)
		{
			back->next = back->next->next;
		}
	}
}

void PrintLinkedList(Node* head) noexcept
{
	while (head != nullptr)
	{
		std::cout << head->value << " ";

		head = head->next;
	}

	std::cout << std::endl;
}

int main(int argc, const char* argv[])
{
	Node* n1 = new Node(4);
	Node* n2 = new Node(8, n1);
	Node* n3 = new Node(10, n2);
	Node* n4 = new Node(3, n3);
	Node* n5 = new Node(9, n4);
	Node* n6 = new Node(7, n5);
	Node* n7 = new Node(1, n6);
	Node* n8 = new Node(2, n7);

	PrintLinkedList(n8);

	RemoveKthLastElementFromList(n8, 3);

	PrintLinkedList(n8);
	
	std::cin.get();

	return 0;
}