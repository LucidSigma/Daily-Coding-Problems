#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

unsigned int GetSeatRearrangeCount(const std::vector<bool>& seats)
{
	unsigned int rearrangeCount = 0;
	std::vector<size_t> takenSeats;

	for (size_t i = 0; i < seats.size(); ++i)
	{
		if (seats[i])
		{
			takenSeats.push_back(i);
		}
	}

	if (takenSeats.empty())
	{
		return 0;
	}

	const size_t median = takenSeats.size() / 2;
	unsigned int currentSeat = 1;

	for (size_t i = 0; i < median; ++i)
	{
		rearrangeCount += takenSeats[median] - takenSeats[i] - currentSeat;
		++currentSeat;
	}

	currentSeat = 1;

	for (size_t i = median + 1; i < takenSeats.size(); ++i)
	{
		rearrangeCount += takenSeats[i] - (takenSeats[median] + currentSeat);
		++currentSeat;
	}

	return rearrangeCount;
}

int main(const int argc, const char* const argv[])
{
	std::cout << GetSeatRearrangeCount({ false, true, true, false, true, false, false, false, true }) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}