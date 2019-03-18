#include <iostream>
#include <memory>
#include <vector>

struct Node
{
	int value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(int value, const std::shared_ptr<Node> left = nullptr, const std::shared_ptr<Node> right = nullptr) noexcept
		: value(value), left(left), right(right)
	{ }
};

void GetAllRootPathsHelper(const std::shared_ptr<Node>& node, std::vector<int>& currentPath, std::vector<std::vector<int>>& allPaths) noexcept
{
	currentPath.push_back(node->value);

	if (node->left == nullptr && node->right == nullptr)
	{
		allPaths.push_back(currentPath);
	}
	else
	{
		GetAllRootPathsHelper(node->left, currentPath, allPaths);
		currentPath.pop_back();

		GetAllRootPathsHelper(node->right, currentPath, allPaths);
		currentPath.pop_back();
	}
}

std::vector<std::vector<int>> GetAllRootPaths(const std::shared_ptr<Node>& root) noexcept
{
	if (root == nullptr)
	{
		return { };
	}
	
	std::vector<std::vector<int>> allPaths;
	std::vector<int> currentPath;

	GetAllRootPathsHelper(root, currentPath, allPaths);

	return allPaths;
}

template <typename T>
void PrintVector(const std::vector<T>& values) noexcept
{
	for (const auto& value : values)
	{
		std::cout << value << " ";
	}
}

template <typename T>
void PrintVectorOfVectors(const std::vector<std::vector<T>>& vectors) noexcept
{
	for (const auto& vector : vectors)
	{
		std::cout << "[ ";
		PrintVector(vector);
		std::cout << "]\n";
	}
}

int main(int argc, char* argv[])
{
	auto n5 = std::make_shared<Node>(5);
	auto n4 = std::make_shared<Node>(4);
	auto n3 = std::make_shared<Node>(3, n4, n5);
	auto n2 = std::make_shared<Node>(2);
	auto n1 = std::make_shared<Node>(1, n2, n3);

	PrintVectorOfVectors(GetAllRootPaths(n1));

	std::cin.get();

	return 0;
}
