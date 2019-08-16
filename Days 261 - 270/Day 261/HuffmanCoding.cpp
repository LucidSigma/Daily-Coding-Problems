#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>

struct Node
{
	char letter;
	unsigned int count;

	std::shared_ptr<Node> left = nullptr;
	std::shared_ptr<Node> right = nullptr;

	Node(const char letter, const unsigned int count)
		: letter(letter), count(count)
	{ }
};

inline bool operator >(const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs)
{
	return lhs->count > rhs->count;
}

std::shared_ptr<Node> CreateHuffmanTreeHelper(std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, std::greater<std::shared_ptr<Node>>>& nodeQueue)
{
	if (nodeQueue.size() == 1)
	{
		const auto node = nodeQueue.top();
		nodeQueue.pop();

		return node;
	}

	const auto leftNode = nodeQueue.top();
	nodeQueue.pop();

	const auto rightNode = nodeQueue.top();
	nodeQueue.pop();

	const auto parentNode = std::make_shared<Node>('*', leftNode->count + rightNode->count);
	parentNode->left = leftNode;
	parentNode->right = rightNode;
	
	nodeQueue.push(parentNode);

	return CreateHuffmanTreeHelper(nodeQueue);
}

std::shared_ptr<Node> CreateHuffmanTree(const std::unordered_map<char, unsigned int>& frequencies)
{
	std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, std::greater<std::shared_ptr<Node>>> nodeQueue;

	for (const auto [letter, count] : frequencies)
	{
		nodeQueue.push(std::make_shared<Node>(letter, count));
	}

	return CreateHuffmanTreeHelper(nodeQueue);
}

std::ostream& operator <<(std::ostream& outputStream, const std::shared_ptr<Node>& node)
{
	if (node == nullptr)
	{
		outputStream << "- ";
	}
	else
	{
		outputStream << node->letter << " " << node->left << node->right;
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	const std::unordered_map<char, unsigned int> frequencies
	{
		{ 'c', 4 },
		{ 'a', 15 },
		{ 't', 12 },
		{ 's', 2 }
	};

	std::cout << CreateHuffmanTree(frequencies) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}