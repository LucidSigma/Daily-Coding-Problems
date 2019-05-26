#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

struct Node
{
	int value;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;
	
	explicit Node(const int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr)
		: value(value), left(left), right(right)
	{ }
};

std::shared_ptr<Node> GetTreeFromPostorderTraversal(const std::vector<int>& values) noexcept
{
	auto head = std::make_shared<Node>(values.back());

	if (values.size() == 1)
	{
		return head;
	}

	unsigned int partitionIndex = 0;

	for (unsigned int i = 0; i < values.size() - 1; ++i)
	{
		if (values[i] > head->value)
		{
			partitionIndex = i;

			break;
		}
	}

	std::vector<int> lesserValues{ std::cbegin(values), std::cbegin(values) + partitionIndex };
	std::vector<int> greaterValues{ std::cbegin(values) + partitionIndex, std::cend(values) - 1 };

	head->left = !lesserValues.empty() ? GetTreeFromPostorderTraversal(lesserValues) : nullptr;
	head->right = !greaterValues.empty() ? GetTreeFromPostorderTraversal(greaterValues) : nullptr;

	return head;
}

std::ostream& operator <<(std::ostream& outputStream, const std::shared_ptr<Node>& head) noexcept
{
	if (head == nullptr)
	{
		outputStream << "- ";
	}
	else
	{
		outputStream << head->value << " " << head->left << head->right;
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	const auto tree = GetTreeFromPostorderTraversal({ 2, 4, 3, 8, 7, 5 });

	std::cout << tree << "\n";

	std::cin.get();

	return 0;
}