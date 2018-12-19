#include <algorithm>
#include <array>
#include <iostream>
#include <utility>

template <unsigned int Size>
unsigned int FindClassroomCount(const std::array<std::pair<int, int>, Size>& intervals)
{
	std::array<int, Size> starts;
	std::array<int, Size> ends;

	for (unsigned int i = 0; i < Size; i++)
	{
		starts[i] = intervals[i].first;
		ends[i] = intervals[i].second;
	}

	std::sort(starts.begin(), starts.end());
	std::sort(ends.begin(), ends.end());

	unsigned int currentClassroomsNeeded = 1;
	unsigned int totalClassroomsNeeded = 1;
	unsigned int i = 1;
	unsigned int j = 0;

	while ((i < Size) && (j < Size))
	{
		if (starts[i] <= ends[j])
		{
			currentClassroomsNeeded++;
			i++;

			if (currentClassroomsNeeded > totalClassroomsNeeded)
			{
				totalClassroomsNeeded = currentClassroomsNeeded;
			}
		}
		else
		{
			currentClassroomsNeeded--;
			j++;
		}
	}

	return totalClassroomsNeeded;
}

int main(int argc, const char* argv[])
{
	std::array<std::pair<int, int>, 3> times { std::make_pair(30, 75), std::make_pair(0, 50), std::make_pair(60, 150) };

	std::cout << "Classrooms needed: " << FindClassroomCount(times) << std::endl;

	std::cin.get();

	return 0;
}