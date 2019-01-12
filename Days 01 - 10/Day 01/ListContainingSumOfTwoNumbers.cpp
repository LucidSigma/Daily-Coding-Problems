#include <iostream>
#include <unordered_set>
#include <type_traits>
#include <vector>

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
bool ContainsTwoNumberSum(const std::vector<T>& numberList, T total)
{
	std::unordered_set<T> numberHash;

	for (unsigned int i = 0; i < numberList.size(); i++)
	{
		if (numberHash.find(total - numberList[i]) != numberHash.end())
		{
			return true;
		}
		else
		{
			numberHash.insert(numberList[i]);
		}
	}
	
	return false;
}

int main(int argc, char* argv[])
{
	std::vector<int> numbers { 10, 15, 3, 7 };

	std::cout << std::boolalpha;
	std::cout << ContainsTwoNumberSum(numbers, 17) << "\n";

	std::cin.get();

	return 0;
}
