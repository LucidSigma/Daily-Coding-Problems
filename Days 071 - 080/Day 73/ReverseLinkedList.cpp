#include <iostream>
#include <memory>
#include <string>

struct Node
{
	std::string value;

	std::shared_ptr<Node> next;

	explicit Node(const std::string& value, std::shared_ptr<Node> next = nullptr) noexcept
		: value(value), next(next)
	{ }
};

std::shared_ptr<Node> ReverseLinkedListHelper(std::shared_ptr<Node> head, std::shared_ptr<Node> next) noexcept
{
	if (head == nullptr)
	{
		return next;
	}

	std::shared_ptr<Node> previous = head->next;
	head->next = next;

	return ReverseLinkedListHelper(previous, head);
}

void ReverseLinkedList(std::shared_ptr<Node> head) noexcept
{
	ReverseLinkedListHelper(head, nullptr);
}

void PrintLinkedList(std::shared_ptr<Node> head) noexcept
{
	while (head != nullptr)
	{
		std::cout << head->value << "\n";
		head = head->next;
	}
}

int main(int argc, char* argv[])
{
	std::shared_ptr<Node> n1 = std::make_shared<Node>("1");
	std::shared_ptr<Node> n2 = std::make_shared<Node>("2", n1);
	std::shared_ptr<Node> n3 = std::make_shared<Node>("3", n2);
	std::shared_ptr<Node> n4 = std::make_shared<Node>("4", n3);
	std::shared_ptr<Node> n5 = std::make_shared<Node>("5", n4);
	std::shared_ptr<Node> n6 = std::make_shared<Node>("6", n5);
	std::shared_ptr<Node> n7 = std::make_shared<Node>("7", n6);
	std::shared_ptr<Node> n8 = std::make_shared<Node>("8", n7);
	
	std::cout << "Printing from tail:\n";
	PrintLinkedList(n1);

	std::cout << "\nPrinting from head:\n";
	PrintLinkedList(n8);

	std::cout << "\nREVERSING LIST...\n\n";
	ReverseLinkedList(n8);

	std::cout << "Printing from old tail:\n";
	PrintLinkedList(n1);

	std::cout << "\nPrinting from old head:\n";
	PrintLinkedList(n8);

	std::cin.get();

	return 0;
}