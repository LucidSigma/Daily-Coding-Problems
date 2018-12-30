#include <array>
#include <iterator>
#include <iostream>
#include <set>
#include <type_traits>

template <unsigned int Size, typename = std::enable_if_t<(Size > 0)>>
void PrintRunningMedians(const std::array<int, Size>& sequence)
{
	std::multiset<int> sortedSequence;

	for (auto number : sequence)
	{
		sortedSequence.insert(number);
		
		auto medianIterator = sortedSequence.begin();
		std::advance(medianIterator, sortedSequence.size() / 2);

		float median = *medianIterator;

		if (sortedSequence.size() % 2 == 0)
		{
			medianIterator--;
			median += *medianIterator;

			median /= 2.0f;
		}

		std::cout << median << "\n";
	}
}

int main(int argc, const char* argv[])
{
	PrintRunningMedians<7>({ 2, 1, 5, 7, 2, 0, 5 });

	std::cin.get();

	return 0;
}