#include <iostream>

struct Node
{
public:
	int value;

	Node* left;
	Node* right;
	Node* parent;

	bool isLocked;
	unsigned int descendantLockCount;

	Node(int value, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr) noexcept
		: value(value), left(left), right(right), parent(parent), isLocked(false), descendantLockCount(0)
	{
		if (left != nullptr)
		{
			left->parent = this;
		}

		if (right != nullptr)
		{
			right->parent = this;
		}
	}

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

	inline bool IsLocked() const { return isLocked; }

	bool Lock()
	{
		if (CanBeLocked())
		{
			isLocked = true;

			Node* currentNode = parent;

			while (currentNode != nullptr)
			{
				currentNode->descendantLockCount++;
				currentNode = currentNode->parent;
			}

			return true;
		}
		
		return false;
	}

	bool Unlock()
	{
		if (CanBeLocked())
		{
			isLocked = false;

			Node* currentNode = parent;

			while (currentNode != nullptr)
			{
				currentNode->descendantLockCount--;
				currentNode = currentNode->parent;
			}

			return true;
		}

		return false;
	}

private:
	bool CanBeLocked()
	{
		if (descendantLockCount > 0)
		{
			return false;
		}

		Node* currentNode = parent;

		while (currentNode != nullptr)
		{
			if (currentNode->isLocked)
			{
				return false;
			}

			currentNode = currentNode->parent;
		}

		return true;
	}
};

int main(int argc, const char* argv[])
{
	Node* leftleft = new Node(67);
	Node* leftright = new Node(49);
	
	Node* rightright = new Node(36);

	Node* left = new Node(82, leftleft, leftright);
	Node* right = new Node(49, nullptr, rightright);

	Node* root = new Node(19, left, right);

	std::cout << std::boolalpha;

	std::cout << left->Lock() << "\n";
	std::cout << leftright->Lock() << "\n";

	left->Unlock();

	std::cout << leftright->Lock() << "\n";

	if (leftright->IsLocked())
	{
		std::cout << "Node leftright is locked." << std::endl;
	}

	std::cin.get();

	return 0;
}