#include <array>
#include <iostream>
#include <iterator>
#include <unordered_map>

class SparseArray
{
private:
	std::unordered_map<unsigned int, int> indexToValueMapping;

public:
	template <unsigned int Size>
	SparseArray(const std::array<int, Size>& array) noexcept
	{
		for (unsigned int i = 0; i < array.size(); i++)
		{
			if (array[i] != 0)
			{
				indexToValueMapping[i] = array[i];
			}
		}
	}

	void Set(const unsigned int i, const int value) noexcept
	{
		if (value == 0)
		{
			indexToValueMapping.erase(i);
		}
		else
		{
			indexToValueMapping[i] = value;
		}
	}

	int Get(const unsigned int i) const noexcept
	{
		if (indexToValueMapping.find(i) == std::cend(indexToValueMapping))
		{
			return 0;
		}

		return indexToValueMapping.at(i);
	}
};

int main(int argc, char* argv[])
{
	std::array<int, 10> values { 1, 9, 0, 0, 0, 2, 5, 0, 0, -8 };
	SparseArray sparceArray(values);

	sparceArray.Set(3, 4);
	sparceArray.Set(6, 0);

	for (unsigned int i = 0; i < 10; i++)
	{
		std::cout << sparceArray.Get(i) << " ";
	}

	std::cout << "\n";

	std::cin.get();

	return 0;
}