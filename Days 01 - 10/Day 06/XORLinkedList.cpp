#include <iostream>
#include <stdexcept>

template<typename T>
T* XorAddresses(T* previous, T* next)
{
	return reinterpret_cast<T*>(reinterpret_cast<int>(previous) ^ reinterpret_cast<int>(next));
}

template<typename T>
class XorList
{
private:
	struct Node
	{
		T data;
		Node* xorAddress;

		Node(T data, Node* previous, Node* next)
			: data(data), xorAddress(XorAddresses(previous, next))
		{ }
	};

	Node* head = nullptr;
	unsigned int size = 0;

public:
	XorList() = default;

	~XorList()
	{
		DestroyNode(nullptr, head);
	}

	void Add(T data)
	{
		if (head == nullptr)
		{
			head = new Node(data, nullptr, nullptr);
		}
		else
		{
			Node* previous = nullptr;
			Node* current = head;
			Node* next = XorAddresses(previous, current->xorAddress);

			while (next != nullptr)
			{
				previous = current;
				current = next;
				next = XorAddresses(previous, current->xorAddress);
			}

			Node* node = new Node(data, current, nullptr);
			current->xorAddress = XorAddresses(previous, node);
		}

		size++;
	}

	T Get(unsigned int index) const
	{
		Node* previous = nullptr;
		Node* current = head;

		unsigned int iterationCounter = index;

		while ((iterationCounter > 0) && (current != nullptr))
		{
			Node* next = XorAddresses(previous, current->xorAddress);

			previous = current;
			current = next;

			iterationCounter--;
		}

		if (iterationCounter != 0)
		{
			throw std::out_of_range("Index out of range of XOR linked list.");
		}

		return current->data;
	}

	T operator [](unsigned int index) const
	{
		return Get(index);
	}

	inline unsigned int Size() const noexcept { return size; }

private:
	void DestroyNode(Node* previous, Node* current)
	{
		if (current == nullptr)
		{
			return;
		}
		
		Node* next = XorAddresses(previous, current->xorAddress);

		if (next != nullptr)
		{
			DestroyNode(current, next);

			delete next;
		}
	}
};

int main(int argc, char* argv[])
{
	XorList<int> xorList;

	xorList.Add(10);
	xorList.Add(25);
	xorList.Add(42);

	std::cout << xorList.Get(2) << "\n";
	std::cout << xorList[1] << "\n";
	
	try
	{
		std::cout << xorList[4] << "\n";
	}
	catch (const std::out_of_range& exception)
	{
		std::cout << "Variable out of range.\n";	
	}

	std::cin.get();
	
	return 0;
}
