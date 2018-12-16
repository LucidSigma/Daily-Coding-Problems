#include <array>
#include <deque>
#include <iostream>

template <unsigned int Size>
void PrintSubarrayMaximums(const std::array<int, Size>& array, unsigned int k) noexcept
{
	std::deque<int> elements(k);

	for (unsigned int i = 0; i < k; i++)
	{
		while (!elements.empty() && (array[i] >= array[elements.back()]))
		{
			elements.pop_back();
		}

		elements.push_back(i);
	}

	for (unsigned int i = k; i < array.size(); i++)
	{
		std::cout << array[elements.front()] << " ";

		while (!elements.empty() && (elements.front() <= i - k))
		{
			elements.pop_front();
		}

		while (!elements.empty() && (array[i] >= array[elements.back()]))
		{
			elements.pop_back();
		}

		elements.push_back(i);
	}

	std::cout << array[elements.front()] << std::endl;
}

int main(int argc, char* argv[])
{
	PrintSubarrayMaximums<6>({ 10, 5, 2, 7, 8, 7 }, 3);
	PrintSubarrayMaximums<10>({ 5, 8, 2, 6, 9, 3, 2, 0, 6, 7 }, 4);

	std::cin.get();

	return 0;
}
