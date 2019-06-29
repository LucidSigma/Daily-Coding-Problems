#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static constexpr char IPAddressSeparator = '.';

std::vector<std::string> SplitString(const std::string& text, const char delimiter = ' ') noexcept
{
	std::string currentToken;
	std::istringstream reader(text);

	std::vector<std::string> tokens;

	while (std::getline(reader, currentToken, delimiter))
	{
		tokens.push_back(currentToken);
	}

	return tokens;
}

bool IsIPAddressValid(const std::string& ipAddress) noexcept
{
	const auto ipAddressParts = SplitString(ipAddress, IPAddressSeparator);

	for (const auto& part : ipAddressParts)
	{
		if (part.length() > 3 || std::stoi(part) < 0 || std::stoi(part) > 255)
		{
			return false;
		}
		
		if (part.length() > 1 && std::stoi(part) == 0)
		{
			return false;
		}

		if (part.length() > 1 && std::stoi(part) != 0 && part[0] == '0')
		{
			return false;
		}
	}

	return true;
}

std::vector<std::string> GetAllValidIPAddresses(const std::string& digits) noexcept
{
	if (static constexpr unsigned int MaxIPAddressLength = 12u;
		digits.size() > MaxIPAddressLength)
	{
		return { };
	}

	std::vector<std::string> validIPAddresses;

	for (unsigned int i = 1; i < digits.size() - 2; ++i)
	{
		for (unsigned int j = i + 1; j < digits.size() - 1; ++j)
		{
			for (unsigned int k = j + 1; k < digits.size(); ++k)
			{
				std::string currentIPAddress = digits;

				currentIPAddress = currentIPAddress.substr(0, k) + IPAddressSeparator + currentIPAddress.substr(k);
				currentIPAddress = currentIPAddress.substr(0, j) + IPAddressSeparator + currentIPAddress.substr(j);
				currentIPAddress = currentIPAddress.substr(0, i) + IPAddressSeparator + currentIPAddress.substr(i);

				if (IsIPAddressValid(currentIPAddress))
				{
					validIPAddresses.push_back(currentIPAddress);
				}
			}
		}
	}

	return validIPAddresses;
}

template <typename T>
std::ostream& operator <<(std::ostream& outputStream, const std::vector<T>& values) noexcept
{
	for (const auto& value : values)
	{
		outputStream << value << "\n";
	}

	return outputStream;
}

int main(int argc, char* argv[])
{
	std::cout << GetAllValidIPAddresses("2542540123") << "\n";

	std::cin.get();

	return 0;
}