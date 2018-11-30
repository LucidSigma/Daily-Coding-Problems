#include <iostream>
#include <unordered_set>
#include <type_traits>
#include <vector>

template<typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
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
	std::vector<int> numbers { 10, 15, 3, 7, 34, 2, 9, 6, 17, 5, -4 };

	std::cout << std::boolalpha;

	std::cout << ContainsTwoNumberSum(numbers,  1) << std::endl;	// true
	std::cout << ContainsTwoNumberSum(numbers, 17) << std::endl;	// true
	std::cout << ContainsTwoNumberSum(numbers, 41) << std::endl;	// true
	std::cout << ContainsTwoNumberSum(numbers, 29) << std::endl;	// false
	std::cout << ContainsTwoNumberSum(numbers, 13) << std::endl;	// true
	std::cout << ContainsTwoNumberSum(numbers, 15) << std::endl;	// true
	std::cout << ContainsTwoNumberSum(numbers, 64) << std::endl;	// false
	std::cout << ContainsTwoNumberSum(numbers, 23) << std::endl;	// true
	std::cout << ContainsTwoNumberSum(numbers,  7) << std::endl;	// true
	std::cout << ContainsTwoNumberSum(numbers, -1) << std::endl;	// true
	std::cout << ContainsTwoNumberSum(numbers, 43) << std::endl;	// true
	std::cout << ContainsTwoNumberSum(numbers, 28) << std::endl;	// false
	std::cout << ContainsTwoNumberSum(numbers, 16) << std::endl;	// true
	std::cout << ContainsTwoNumberSum(numbers,  6) << std::endl;	// true
	std::cout << ContainsTwoNumberSum(numbers, 19) << std::endl;	// true

	std::cin.get();

	return 0;
}
