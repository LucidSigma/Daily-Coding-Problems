#include <iostream>

template<typename T>
struct Node
{
	int value;
	
	Node* left = nullptr;
	Node* right = nullptr;

	Node(int value, Node* left, Node* right)
		: value(value), left(left), right(right)
	{ }
};

template<typename T>
bool IsUnival(Node<T>* node, unsigned int& counter)
{
	if (node == nullptr)
	{
		return true;
	}

	bool isLeftUnival = IsUnival(node->left, counter);
	bool isRightUnival = IsUnival(node->right, counter);

	if (!isLeftUnival || !isRightUnival)
	{
		return false;
	}

	if ((node->left != nullptr) && (node->value != node->left->value))
	{
		return false;
	}

	if ((node->right != nullptr) && (node->value != node->right->value))
	{
		return false;
	}

	counter++;

	return true;
}

template<typename T>
unsigned int GetUnivalTreeCount(Node<T>* root)
{
	unsigned int count = 0;

	return (IsUnival(root, count), count);
}

template<typename T>
void FreeNodeMemory(Node<T>* root)
{
	if (root == nullptr)
	{
		return;
	}

	FreeNodeMemory(root->left);
	FreeNodeMemory(root->right);

	delete root;
	root = nullptr;
}

int main(int argc, char* argv[])
{
	Node<int>* grandGrandChildA = new Node<int>(1, nullptr, nullptr);
	Node<int>* grandGrandChildB = new Node<int>(1, nullptr, nullptr);

	Node<int>* grandChildA = new Node<int>(1, grandGrandChildA, grandGrandChildB);
	Node<int>* grandChildB = new Node<int>(0, nullptr, nullptr);

	Node<int>* childA = new Node<int>(1, nullptr, nullptr);
	Node<int>* childB = new Node<int>(0, grandChildA, grandChildB);

	Node<int>* root = new Node<int>(0, childA, childB);

	std::cout << GetUnivalTreeCount(root) << std::endl;

	FreeNodeMemory(root);

	std::cin.get();

	return 0;
}