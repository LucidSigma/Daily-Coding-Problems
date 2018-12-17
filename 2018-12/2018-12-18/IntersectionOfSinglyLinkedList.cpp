#include <cmath>
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

unsigned int GetSinglyLinkedListLength(Node*& list) noexcept
{
	unsigned int count = 0;

	while (list != nullptr)
	{
		list = list->next;
		count++;
	}

	return count;
}

Node* GetSinglyLinkedListIntersection(Node* listA, Node* listB) noexcept
{
	Node* listACounter = listA;
	Node* listBCounter = listB;

	unsigned int lengthA = GetSinglyLinkedListLength(listACounter);
	unsigned int lengthB = GetSinglyLinkedListLength(listBCounter);

	if (listACounter != listBCounter)
	{
		return nullptr;
	}

	unsigned int difference = std::abs(static_cast<int>(lengthA) - static_cast<int>(lengthB));
	Node* shorterList = nullptr;
	Node* longerList = nullptr;

	if (lengthA > lengthB)
	{
		shorterList = listB;
		longerList = listA;
	}
	else
	{
		shorterList = listA;
		longerList = listB;
	}

	while (difference > 0)
	{
		longerList = longerList->next;
		difference--;
	}

	while (longerList != shorterList)
	{
		longerList = longerList->next;
		shorterList = shorterList->next;
	}

	return longerList;
}

int main(int argc, const char* argv[])
{
	// Intersection
	Node* node10 = new Node(10);
	Node* node8 = new Node(8, node10);

	// List A
	Node* node7 = new Node(7, node8);
	Node* node3 = new Node(3, node7);

	// List B
	Node* node1 = new Node(1, node8);
	Node* node99 = new Node(99, node1);

	std::cout << GetSinglyLinkedListIntersection(node3, node99)->value << std::endl;

	std::cin.get();

	return 0;
}