#include <iostream>
#include <iterator>
#include <memory>
#include <unordered_map>

struct Node
{
	int value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(const int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr) noexcept
		: value(value), left(left), right(right)
	{ }
};

int GetMostFrequentSumInTreeHelper(const std::shared_ptr<Node>& root, std::unordered_map<int, unsigned int>& sumCounts) noexcept
{
	if (root == nullptr)
	{
		return 0;
	}

	int currentTreeSum = root->value + GetMostFrequentSumInTreeHelper(root->left, sumCounts) + GetMostFrequentSumInTreeHelper(root->right, sumCounts);

	if (sumCounts.find(currentTreeSum) == std::cend(sumCounts))
	{
		sumCounts[currentTreeSum] = 0;
	}

	++sumCounts[currentTreeSum];

	return currentTreeSum;
}

int GetMostFrequentSumInTree(const std::shared_ptr<Node>& root) noexcept
{
	std::unordered_map<int, unsigned int> sumCounts;
	unsigned int maxCount = 0;
	int mostFrequentSum = 0;

	GetMostFrequentSumInTreeHelper(root, sumCounts);	
	
	for (const auto [sum, count] : sumCounts)
	{
		if (count > maxCount)
		{
			maxCount = count;
			mostFrequentSum = sum;
		}
	}

	return mostFrequentSum;
}

int main(int argc, char* argv[])
{
	const auto left = std::make_shared<Node>(2);
	const auto right = std::make_shared<Node>(-5);
	const auto root = std::make_shared<Node>(5, left, right);

	std::cout << GetMostFrequentSumInTree(root) << "\n";

	std::cin.get();

	return 0;
}