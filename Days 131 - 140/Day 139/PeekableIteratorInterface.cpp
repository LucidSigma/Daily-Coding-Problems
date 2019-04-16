#include <iostream>
#include <stdexcept>
#include <vector>

class Iterator
{
private:
	unsigned int currentIndex = 0;
	const std::vector<int>& container;

public:
	explicit Iterator(const std::vector<int>& vector) noexcept
		: container(vector)
	{ }

	int Next()
	{
		currentIndex++;

		if (currentIndex == container.size())
		{
			throw std::runtime_error("Iterator passed index bounds of container.");
		}

		return container[currentIndex];
	}

	inline bool HasNext() const noexcept
	{
		return currentIndex < container.size() - 1;
	}
};

class PeekableInterface
{
private:
	Iterator& iterator;

public:
	explicit PeekableInterface(Iterator& iterator)
		: iterator(iterator)
	{ }

	int Peek()
	{
		Iterator clonedIterator = iterator;

		return clonedIterator.Next();
	}

	inline int Next()
	{
		return iterator.Next();
	}

	inline bool HasNext() const noexcept
	{
		return iterator.HasNext();
	}
};

int main(int argc, char* argv[])
{
	const std::vector<int> values { 1, 2, 3, 4, 5 };
	Iterator iterator(values);
	PeekableInterface peekIterator(iterator);

	for (unsigned int i = 0; i < 2; i++)
	{
		std::cout << iterator.Next() << " ";
	}
	
	std::cout << "\n" << peekIterator.Peek() << "\n";
	std::cout << iterator.Next() << "\n";

	std::cin.get();

	return 0;
}