#include <iostream>
#include <unordered_set>
#include <vector>

bool ContainsTwoNumberSum(const std::vector<int>& numberList, int total)
{
	std::unordered_set<int> numberHash;

	for (unsigned int i = 0; i < numberList.size(); i++)
	{
		if (numberHash.find(total - numberList[i]) != numberHash.end())
		{
			return true;
		}
		
		numberHash.insert(numberList[i]);
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
