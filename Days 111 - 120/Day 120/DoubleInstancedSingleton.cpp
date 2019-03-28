#include <iostream>

class DoubleSingleton final
{
private:
	DoubleSingleton() noexcept = default;
	~DoubleSingleton() noexcept = default;

public:
	DoubleSingleton(const DoubleSingleton&) noexcept = delete;
	DoubleSingleton(DoubleSingleton&&) noexcept = delete;

	DoubleSingleton& operator =(const DoubleSingleton&) noexcept = delete;
	DoubleSingleton& operator =(DoubleSingleton&&) noexcept = delete;

	static DoubleSingleton& GetInstance() noexcept
	{
		static DoubleSingleton instanceA;
		static DoubleSingleton instanceB;
		static bool instanceDecider = true;

		instanceDecider = !instanceDecider;

		return instanceDecider ? instanceA : instanceB;
	}
};

int main(int argc, char* argv[])
{
	std::cout << &DoubleSingleton::GetInstance() << "\n";	// Instance 2
	std::cout << &DoubleSingleton::GetInstance() << "\n";	// Instance 1
	std::cout << &DoubleSingleton::GetInstance() << "\n";	// Instance 2
	std::cout << &DoubleSingleton::GetInstance() << "\n";	// Instance 1

	std::cin.get();

	return 0;
}
