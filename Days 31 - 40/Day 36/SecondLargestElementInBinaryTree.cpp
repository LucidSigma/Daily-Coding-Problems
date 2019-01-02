#include <initializer_list>
#include <iostream>
#include <limits>

struct Node
{
	Node* left;
	Node* right;

	int value;

	Node(int value, Node* left = nullptr, Node* right = nullptr)
		: value(value), left(left), right(right)
	{ }

	~Node() noexcept
	{
		if (left != nullptr)
		{
			delete left;
		}

		if (right != nullptr)
		{
			delete right;
		}
	}
};

class BinarySearchTree
{
private:
	Node* root = nullptr;

	unsigned int count = 0;

public:
	BinarySearchTree() = default;

	BinarySearchTree(const std::initializer_list<int>& values)
	{
		Insert(values);
	}

	~BinarySearchTree() noexcept
	{
		if (root != nullptr)
		{
			delete root;
		}
	}

	void Insert(int value)
	{
		if (root == nullptr)
		{
			root = new Node(value);
		}
		else
		{
			InsertHelper(root, value);
		}

		count++;
	}

	void Insert(const std::initializer_list<int>& values)
	{
		for (const auto value : values)
		{
			Insert(value);
		}
	}

	inline Node* const GetRoot() { return root; }
	inline unsigned int GetCount() const { return count; }

private:
	Node* InsertHelper(Node* node, int value)
	{
		if (node == nullptr)
		{
			return new Node(value);
		}

		if (value < node->value)
		{
			node->left = InsertHelper(node->left, value);
		}
		else if (value > root->value)
		{
			node->right = InsertHelper(node->right, value);
		}

		return node;
	}
};

void SecondLargestHelper(Node* node, unsigned int& counter, int& secondLargest)
{
	if ((node == nullptr) || (counter >= 2))
	{
		return;
	}

	SecondLargestHelper(node->right, counter, secondLargest);

	counter++;

	if (counter == 2)
	{
		secondLargest = node->value;

		return;
	}

	SecondLargestHelper(node->left, counter, secondLargest);
}

int SecondLargest(BinarySearchTree& binaryTree)
{
	unsigned int counter = 0;
	int secondLargest = std::numeric_limits<int>::min();

	if ((binaryTree.GetRoot() != nullptr) && (binaryTree.GetCount() >= 2))
	{
		SecondLargestHelper(binaryTree.GetRoot(), counter, secondLargest);
	}
	else
	{
		std::cerr << "Binary tree not large enough.\n";
	}

	return secondLargest;
}

int main(int argc, const char* argv[])
{
	BinarySearchTree tree({ 50, 30, 20, 40, 70, 60, 80 });

	std::cout << "Second largest element in binary tree: " << SecondLargest(tree) << "\n";

	std::cin.get();

	return 0;
}