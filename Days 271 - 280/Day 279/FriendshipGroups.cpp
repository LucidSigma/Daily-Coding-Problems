#include <cstdlib>
#include <iostream>
#include <iterator>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void GetFriendshipGroupsHelper(const unsigned int currentPerson, const std::unordered_map<unsigned int, std::unordered_set<unsigned int>>& friendships, std::unordered_set<unsigned int>& currentFriendshipGroup)
{
	currentFriendshipGroup.insert(currentPerson);
	const auto friendList = friendships.at(currentPerson);

	if (friendList.empty())
	{
		return;
	}

	for (const auto person : friendList)
	{
		if (currentFriendshipGroup.find(person) == std::cend(currentFriendshipGroup))
		{
			GetFriendshipGroupsHelper(person, friendships, currentFriendshipGroup);
		}
	}
}

std::vector<std::unordered_set<unsigned int>> GetFriendshipGroups(const std::unordered_map<unsigned int, std::unordered_set<unsigned int>>& friendships)
{
	std::vector<std::unordered_set<unsigned int>> friendshipGroups;
	unsigned int personCount = friendships.size();
	std::set<unsigned int> people;

	for (unsigned int i = 0; i < personCount; ++i)
	{
		people.insert(i);
	}

	while (personCount > 0)
	{
		std::unordered_set<unsigned int> currentFriendshipGroup;
		const unsigned int currentPerson = *std::cbegin(people);

		GetFriendshipGroupsHelper(currentPerson, friendships, currentFriendshipGroup);

		friendshipGroups.push_back(currentFriendshipGroup);
		
		for (const auto person : currentFriendshipGroup)
		{
			people.erase(person);
		}

		personCount = people.size();
	}

	return friendshipGroups;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::unordered_set<T>& values)
{
	outputStream << "{ ";

	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	outputStream << "}";

	return outputStream;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	const std::unordered_map<unsigned int, std::unordered_set<unsigned int>> friendshipGroups
	{
		{ 0, { 1, 2 } },
		{ 1, { 0, 5 } },
		{ 2, { 0 } },
		{ 3, { 6 } },
		{ 4, { } },
		{ 5, { 1 } },
		{ 6, { 3 } }
	};

	std::cout << GetFriendshipGroups(friendshipGroups) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}