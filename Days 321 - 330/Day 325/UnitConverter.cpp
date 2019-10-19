#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>

class UnitConverter
{
private:
	std::unordered_map<std::string, float> m_unitConversions;

public:
	UnitConverter() = default;

	void AddConversion(const std::string& fromUnit, const std::string& toUnit, const unsigned int fromQuantity, const unsigned int toQuantity)
	{
		if (m_unitConversions.find(fromUnit) == std::cend(m_unitConversions))
		{
			m_unitConversions[fromUnit] = 1.0f;
		}

		m_unitConversions[toUnit] = static_cast<float>(toQuantity) / static_cast<float>(fromQuantity)* m_unitConversions[fromUnit];
	}

	float Convert(const std::string& fromUnit, const std::string& toUnit, const unsigned int fromQuantity) const
	{
		const float conversion = static_cast<float>(fromQuantity) / m_unitConversions.at(fromUnit);

		return conversion * m_unitConversions.at(toUnit);
	}
};

int main(const int argc, const char* const argv[])
{
	UnitConverter converter;
	converter.AddConversion("inch", "foot", 12, 1);
	converter.AddConversion("foot", "yard", 3, 1);
	converter.AddConversion("yard", "chain", 22, 1);
	
	std::cout << converter.Convert("inch", "yard", 100) << "\n";
	std::cout << converter.Convert("foot", "chain", 16) << "\n";
	std::cout << converter.Convert("yard", "feet", 4096) << "\n";

	std::cin.get();

	return EXIT_SUCCESS;
}