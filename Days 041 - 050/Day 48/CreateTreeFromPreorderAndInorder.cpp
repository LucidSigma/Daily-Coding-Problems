#include <iostream>
#include <string>
#include <vector>

struct Node
{
	std::string value;

	Node* left;
	Node* right;

	explicit Node(const std::string& value) noexcept
		: value(value), left(nullptr), right(nullptr)
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

Node* CreateTree(const std::vector<std::string>& preorder, const std::vector<std::string>& inorder)
{
	if (preorder.empty() || inorder.empty())
	{
		return nullptr;
	}

	Node* rootNode = new Node(preorder[0]);

	if (preorder.size() == 1)
	{
		return rootNode;
	}

	for (unsigned int i = 0; i < inorder.size(); i++)
	{
		if (inorder[i] == rootNode->value)
		{
			std::vector<std::string> shorteningPreorder(preorder.begin() + 1, preorder.begin() + i + 1);
			std::vector<std::string> shorteningInorder(inorder.begin(), inorder.begin() + i + 1);

			rootNode->left = CreateTree(shorteningPreorder, shorteningInorder);

			shorteningPreorder = std::vector<std::string>(preorder.begin() + i + 1, preorder.end());
			shorteningInorder = std::vector<std::string>(inorder.begin() + i + 1, inorder.end());

			rootNode->right = CreateTree(shorteningPreorder, shorteningInorder);
		}
	}

	return rootNode;
}

int main(int argc, const char* argv[])
{
	Node* tree = CreateTree({ "a", "b", "d", "e", "c", "f", "g" }, { "d", "b", "e", "a", "f", "c", "g" });
	std::cout << tree->left->left->value << "\n";

	delete tree;

	std::cin.get();

	return 0;
}