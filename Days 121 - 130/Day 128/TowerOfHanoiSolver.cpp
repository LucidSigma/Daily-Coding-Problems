#include <iostream>

void SolveTowerOfHanoiHelper(const unsigned int discCount, const char startTower, const char auxiliaryTower, const char goalTower) noexcept
{
	if (discCount == 1)
	{
		std::cout << "Moved disc " << discCount << " from tower " << startTower << " to tower " << goalTower << ".\n";
	}
	else
	{
		SolveTowerOfHanoiHelper(discCount - 1, startTower, goalTower, auxiliaryTower);

		std::cout << "Moved disc " << discCount << " from tower " << startTower << " to tower " << goalTower << ".\n";

		SolveTowerOfHanoiHelper(discCount - 1, auxiliaryTower, startTower, goalTower);
	}
}

inline void SolveTowerOfHanoi(const unsigned int discCount) noexcept
{
	std::cout << "Solution for Tower of Hanoi with " << discCount << " discs:\n";

	SolveTowerOfHanoiHelper(3, 'A', 'B', 'C');
}

int main(int argc, char* argv[])
{
	SolveTowerOfHanoi(3);

	std::cin.get();

	return 0;
}