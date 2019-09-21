#include <cstdlib>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>

using Customer = unsigned int;
using Drink = unsigned int;
using DrinkPreferences = std::unordered_map<Customer, std::unordered_set<Drink>>;

std::unordered_set<Drink> GetMinPossibleDrinksHelper(const std::unordered_set<Drink>& drinks, const std::unordered_set<Drink>& leftoverDrinks, const std::unordered_set<Customer>& leftoverCustomers, const std::unordered_map<Drink, std::unordered_set<Customer>>& drinkCustomers)
{
	std::unordered_set<Drink> minDrinks = drinks;

	if (leftoverCustomers.empty())
	{
		for (const auto drink : leftoverDrinks)
		{
			minDrinks.erase(drink);
		}

		return minDrinks;
	}

	for (const auto drink : leftoverDrinks)
	{
		auto currentLeftoverDrinks = leftoverDrinks;
		currentLeftoverDrinks.erase(drink);

		auto currentLeftoverCustomers = leftoverCustomers;

		for (const auto customer : drinkCustomers.at(drink))
		{
			currentLeftoverCustomers.erase(customer);
		}

		const auto currentMinDrinks = GetMinPossibleDrinksHelper(drinks, currentLeftoverDrinks, currentLeftoverCustomers, drinkCustomers);

		if (currentMinDrinks.size() < minDrinks.size())
		{
			minDrinks = currentMinDrinks;
		}
	}

	return minDrinks;
}

std::unordered_set<Drink> GetMinPossibleDrinks(const DrinkPreferences& preferences)
{
	std::unordered_map<Drink, std::unordered_set<Customer>> drinkCustomers;

	for (const auto& [customer, preferenceList] : preferences)
	{
		for (const auto drink : preferenceList)
		{
			if (drinkCustomers.find(drink) == std::cend(drinkCustomers))
			{
				drinkCustomers[drink] = { };
			}

			drinkCustomers[drink].insert(customer);
		}
	}

	std::unordered_set<Drink> allDrinks;

	for (const auto& [drink, _] : drinkCustomers)
	{
		allDrinks.insert(drink);
	}

	std::unordered_set<Drink> leftoverDrinks = allDrinks;
	std::unordered_set<Customer> leftoverCustomers;

	for (const auto& [customer, _] : preferences)
	{
		leftoverCustomers.insert(customer);
	}

	return GetMinPossibleDrinksHelper(allDrinks, leftoverDrinks, leftoverCustomers, drinkCustomers);
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::unordered_set<T>& set)
{
	for (const auto& value : set)
	{
		outputStream << value << " ";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	const DrinkPreferences preferences
	{
		{ 0, { 0, 1, 3, 6 } },
		{ 1, { 1, 4, 7 } },
		{ 2, { 2, 4, 7, 5 } },
		{ 3, { 3, 2, 5 } },
		{ 4, { 5, 8 } }
	};

	std::cout << GetMinPossibleDrinks(preferences) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}