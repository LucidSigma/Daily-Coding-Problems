#include <iostream>
#include <memory>
#include <random>

struct Node
{
	int value;

	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;

	explicit Node(const int value, const std::shared_ptr<Node>& left = nullptr, const std::shared_ptr<Node>& right = nullptr) noexcept
		: value(value), left(left), right(right)
	{ }
};

inline int RandomInt() noexcept
{
	static std::random_device randomSeed;
	static std::mt19937 randomEngine(randomSeed());
	static std::uniform_int_distribution<unsigned int> randomRange(1, 100);

	return randomRange(randomEngine);
}

inline bool CoinFlip() noexcept
{
	return RandomInt() % 2 == 0;
}

std::shared_ptr<Node> GenerateBinaryTree() noexcept
{
	bool generateLeft = CoinFlip();
	bool generateRight = CoinFlip();

	return std::make_shared<Node>(RandomInt(), generateLeft ? GenerateBinaryTree() : nullptr, generateRight ? GenerateBinaryTree() : nullptr);
}

void PrintBinaryTree(const std::shared_ptr<Node>& root) noexcept
{
	if (root != nullptr)
	{
		std::cout << root->value << " ";
		
		PrintBinaryTree(root->left);
		PrintBinaryTree(root->right);
	}
	else
	{
		static constexpr char NullNode = '-';

		std::cout << NullNode << " ";
	}
}

int main(int argc, char* argv[])
{
	PrintBinaryTree(GenerateBinaryTree());

	std::cout << "\n";

	std::cin.get();

	return 0;
}