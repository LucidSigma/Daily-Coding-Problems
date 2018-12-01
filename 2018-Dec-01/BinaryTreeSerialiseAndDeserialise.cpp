#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Node
{
	std::string val;

	Node* left;
	Node* right;

	Node(const std::string& val, Node* left = nullptr, Node* right = nullptr)
		: val(val), left(left), right(right)
	{}

	~Node()
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

const std::string NULL_NODE = "-";

std::string SerialiseTree(Node* node)
{
	if (node == nullptr)
	{
		return NULL_NODE + " ";
	}

	std::string serialisedTree;

	serialisedTree += node->val + " ";
	serialisedTree += SerialiseTree(node->left);
	serialisedTree += SerialiseTree(node->right);

	return serialisedTree;
}

Node* DeserialiseHelper(std::string& subtree)
{
	std::stringstream scanner(subtree);
	std::string value;

	scanner >> value;

	unsigned int firstIndex = subtree.find_first_of(' ') + 1;
	unsigned int length = subtree.size() - firstIndex;

	subtree = subtree.substr(firstIndex, length);

	if (value == NULL_NODE)
	{
		return nullptr;
	}

	Node* node = new Node(value);
	node->left = DeserialiseHelper(subtree);
	node->right = DeserialiseHelper(subtree);

	return node;
}

Node* DeserialiseTree(const std::string& tree)
{
	std::stringstream scanner(tree);
	std::string treeString(tree);
	std::string value;

	scanner >> value;

	Node* node = new Node(value);
	node = DeserialiseHelper(treeString);
	return node;
}

int main(int argc, char* argv[])
{
	Node* leftLeft = new Node("left.left");
	Node* leftRight = new Node("left.right");
	Node* right = new Node("right");
	Node* left = new Node("left", leftLeft, leftRight);

	Node node("root", left, right);

	std::cout << SerialiseTree(&node) << std::endl;

	assert(DeserialiseTree(SerialiseTree(&node))->left->left->val == "left.left");	// Assertion passes

	std::cin.get();
	
	return 0;
}