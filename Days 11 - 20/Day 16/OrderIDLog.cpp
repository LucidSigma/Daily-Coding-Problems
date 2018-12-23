#include <deque>
#include <iostream>
#include <stdexcept>

class OrderList
{
private:
	unsigned int size;
	std::deque<int> idHistory;

public:
	OrderList(unsigned int size)
		: size(size)
	{ }

	template<typename... Ids>
	void Record(Ids... ids)
	{
		([&](int id) -> void
		{
			idHistory.push_back(id);

			if (idHistory.size() > size)
			{
				idHistory.pop_front();
			}
		}(ids), ...);
	}

	int GetLast(unsigned int i = 0) const
	{
		if (i < idHistory.size())
		{
			return idHistory[idHistory.size() - i - 1];
		}
		else
		{
			throw std::out_of_range("Index out of range.");
		}
	}

	void ChangeSize(unsigned int newSize)
	{
		size = newSize;

		if (size < idHistory.size())
		{
			unsigned int oldSize = idHistory.size();

			for (unsigned int i = 0; i < (oldSize - size); i++)
			{
				idHistory.pop_front();
			}
		}
	}

	std::deque<int>::const_iterator begin() const { return idHistory.cbegin(); }
	std::deque<int>::const_iterator end() const { return idHistory.cend(); }

	inline unsigned int GetCurrentSize() const { return idHistory.size(); }
	inline unsigned int GetMaxSize() const { return size; };
};

int main(int argc, char* argv[])
{
	OrderList orderList(10);
	orderList.Record(1, 45, 6, 3, 8, 3);

	for (unsigned int i = 0; i < orderList.GetCurrentSize(); i++)
	{
		std::cout << orderList.GetLast(i) << "\n";
	}

	std::cout << std::flush;

	std::cin.get();

	return 0;
}