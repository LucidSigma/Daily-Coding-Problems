#include <functional>
#include <iostream>
#include <vector>

using PrintFunction = std::function<void(void)>;

std::vector<PrintFunction> MakeFunctions() noexcept
{
	std::vector<PrintFunction> functionList;

	static unsigned int i = 1;

	for (i = 1; i <= 3; ++i)
	{
		const auto printI = []()
		{
			std::cout << i << "\n";
		};

		functionList.push_back(printI);
	}

	--i;

	return functionList;
}

std::vector<PrintFunction> MakeFunctionsFixed() noexcept
{
	std::vector<PrintFunction> functionList;

	static unsigned int i = 1;

	for (i = 1; i <= 3; ++i)
	{
		const auto printI = [i = i]()
		{
			std::cout << i << "\n";
		};

		functionList.push_back(printI);
	}

	--i;

	return functionList;
}

int main(int argc, char* argv[])
{
	const auto functions = MakeFunctions();

	for (const auto function : functions)
	{
		function();
	}

	std::cout << "\n";

	const auto fixedFunctions = MakeFunctionsFixed();

	for (const auto function : fixedFunctions)
	{
		function();
	}

	std::cin.get();

	return 0;
}