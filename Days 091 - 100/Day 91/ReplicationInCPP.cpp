#include <functional>
#include <iostream>
#include <vector>

void OriginalSnippet() noexcept
{
	std::vector<std::function<unsigned int()>> functions;
	functions.reserve(10);

	unsigned int i;

	for (i = 0; i < 10; i++)
	{
		functions.push_back([&i]() { return i; });
	}

	i--;

	for (const auto& f : functions)
	{
		std::cout << f() << "\n";
	}
}

void DesiredOutcome() noexcept
{
	std::vector<std::function<unsigned int()>> functions;
	functions.reserve(10);	

	for (unsigned int i = 0; i < 10; i++)
	{
		functions.push_back([i]() { return i; });
	}

	for (const auto& f : functions)
	{
		std::cout << f() << "\n";
	}
}

int main(int argc, char* argv[])
{
	OriginalSnippet();

	std::cout << "\n";

	DesiredOutcome();

	std::cin.get();

	return 0;
}