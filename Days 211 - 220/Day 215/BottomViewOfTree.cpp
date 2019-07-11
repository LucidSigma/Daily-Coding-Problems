#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <vector>

struct Node
{
	int value;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	unsigned int depth;

	explicit Node(const int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr) noexcept
		: value{ value }, left{ left }, right{ right }, depth{ 0 }
	{ }
};

void GetBottomViewHelper(std::shared_ptr<Node>& node, std::map<unsigned int, std::shared_ptr<Node>>& depths, const unsigned int currentDepth, const int currentHorizontalDistance) noexcept
{
	node->depth = currentDepth;

	if (depths.find(currentHorizontalDistance) == std::cend(depths) || depths[currentHorizontalDistance]->depth < currentDepth)
	{
		depths[currentHorizontalDistance] = node;
	}

	if (node->left != nullptr)
	{
		GetBottomViewHelper(node->left, depths, currentDepth + 1, currentHorizontalDistance - 1);
	}

	if (node->right != nullptr)
	{
		GetBottomViewHelper(node->right, depths, currentDepth + 1, currentHorizontalDistance + 1);
	}
}

std::vector<int> GetBottomView(std::shared_ptr<Node>& root) noexcept
{
	std::map<unsigned int, std::shared_ptr<Node>> depths;
	GetBottomViewHelper(root, depths, 0, 0);

	std::vector<int> bottomView;
	bottomView.reserve(depths.size());

	for (const auto& [_, node] : depths)
	{
		bottomView.push_back(node->value);
	}

	return bottomView;
}

inline bool operator <(const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs) noexcept
{
	return lhs->value < rhs->value;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values) noexcept
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	auto leftLeftLeft = std::make_shared<Node>(0);
	auto rightRightLeft = std::make_shared<Node>(8);

	auto leftLeft = std::make_shared<Node>(1, leftLeftLeft);
	auto leftRight = std::make_shared<Node>(4);
	auto rightLeft = std::make_shared<Node>(6);
	auto rightRight = std::make_shared<Node>(9, rightRightLeft);

	auto left = std::make_shared<Node>(3, leftLeft, leftRight);
	auto right = std::make_shared<Node>(7, rightLeft, rightRight);

	auto root = std::make_shared<Node>(5, left, right);

	std::cout << GetBottomView(root) << "\n";

	std::cin.get();

	return 0;
}
