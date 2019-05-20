#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <variant>

using Dictionary = std::unordered_map<std::string, int>;

struct NestedDictionary
{
	std::unordered_map<std::string, std::variant<int, NestedDictionary*>> value;
};

Dictionary FlattenNestedDictionaryHelper(const NestedDictionary& nestedDictionary, std::string& currentKey) noexcept
{
	Dictionary flattenedDictionary;

	for (const auto& [key, value] : nestedDictionary.value)
	{
		currentKey += key;

		if (std::holds_alternative<int>(value))
		{
			flattenedDictionary[currentKey] = std::get<int>(value);
			
			if (const std::size_t dotIndex = currentKey.find_last_of('.'); dotIndex == std::string::npos)
			{
				currentKey.clear();
			}
			else
			{
				currentKey = currentKey.substr(0, dotIndex + 1);
			}
		}
		else
		{
			currentKey += '.';

			Dictionary successiveDictionary = FlattenNestedDictionaryHelper(*std::get<NestedDictionary*>(value), currentKey);
			flattenedDictionary.insert(std::cbegin(successiveDictionary), std::cend(successiveDictionary));
		}
	}

	return flattenedDictionary;
}

inline Dictionary FlattenNestedDictionary(const NestedDictionary& nestedDictionary) noexcept
{
	std::string keyTracker;

	return FlattenNestedDictionaryHelper(nestedDictionary, keyTracker);
}

std::ostream& operator <<(std::ostream& outputStream, const Dictionary& dictionary) noexcept
{
	for (const auto& [key, value] : dictionary)
	{
		outputStream << key << ": " << value << "\n";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	NestedDictionary bar;
	bar.value["baz"] = 8;

	NestedDictionary foo;
	foo.value["a"] = 5;
	foo.value["bar"] = &bar;

	NestedDictionary nestedDictionary;
	nestedDictionary.value["key"] = 3;
	nestedDictionary.value["foo"] = &foo;

	std::cout << FlattenNestedDictionary(nestedDictionary) << "\n";

	std::cin.get();

	return 0;
}