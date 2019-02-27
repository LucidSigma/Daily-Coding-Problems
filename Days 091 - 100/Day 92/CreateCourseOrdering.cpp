#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<std::string> GetCourseOrdering(std::unordered_map<std::string, std::vector<std::string>> coursePrerequisites) noexcept
{
	std::vector<std::string> courseOrder;
	courseOrder.reserve(coursePrerequisites.size());

	while (!coursePrerequisites.empty())
	{
		std::unordered_set<std::string> availableCourses;

		for (const auto&[courseName, prerequisites] : coursePrerequisites)
		{
			if (prerequisites.empty())
			{
				courseOrder.push_back(courseName);
				availableCourses.insert(courseName);
			}
		}

		if (availableCourses.empty())
		{
			return { };
		}

		for (auto it = std::begin(coursePrerequisites); it != std::end(coursePrerequisites); it++)
		{
			if (availableCourses.find(it->first) != std::end(availableCourses))
			{
				it = coursePrerequisites.erase(it);

				if (it == std::end(coursePrerequisites))
				{
					break;
				}
			}
		}

		static const auto IsCourseTaken = [&availableCourses](const std::string& name)
		{
			return availableCourses.find(name) != std::end(availableCourses);
		};

		for (auto&[courseName, prerequisites] : coursePrerequisites)
		{
			auto removeIterator = std::remove_if(std::begin(prerequisites), std::end(prerequisites), IsCourseTaken);

			if (removeIterator != std::end(prerequisites))
			{
				prerequisites.erase(removeIterator);
			}
		}
	}

	return courseOrder;
}

template <typename T>
void PrintVector(const std::vector<T>& values) noexcept
{
	for (const auto& value : values)
	{
		std::cout << value << " ";
	}

	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	std::unordered_map<std::string, std::vector<std::string>> coursePrerequisites
	{
		{ "CSC300", { "CSC100", "CSC200" } },
		{ "CSC200", { "CSC100" } },
		{ "CSC100", { } }
	};

	PrintVector(GetCourseOrdering(coursePrerequisites));

	std::cin.get();

	return 0;
}