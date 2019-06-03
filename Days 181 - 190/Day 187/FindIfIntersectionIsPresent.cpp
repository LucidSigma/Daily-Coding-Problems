#include <iostream>
#include <vector>

struct Rectangle
{
	int x;
	int y;

	unsigned int w;
	unsigned int h;
};

bool HasIntersection(const Rectangle& rectA, const Rectangle& rectB) noexcept
{
	const int rectAX2 = rectA.x + static_cast<int>(rectA.w);
	const int rectAY2 = rectA.y + static_cast<int>(rectA.h);

	const int rectBX2 = rectB.x + static_cast<int>(rectB.w);
	const int rectBY2 = rectB.y + static_cast<int>(rectB.h);

	return !(rectA.x < rectBX2 && rectAX2 > rectB.x && rectA.y > rectBY2 && rectAY2 < rectB.y);
}

bool HaveIntersections(const std::vector<Rectangle>& rectangles) noexcept
{
	for (unsigned int i = 0; i < rectangles.size() - 1; ++i)
	{
		for (unsigned int j = i + 1; j < rectangles.size(); ++j)
		{
			if (HasIntersection(rectangles[i], rectangles[j]))
			{
				return true;
			}
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	std::cout << std::boolalpha;
	std::cout << HaveIntersections({ { 1, 4, 3, 3 }, { -1, 3, 2, 1 }, { 0, 5, 4, 3 } }) << "\n";

	std::cin.get();

	return 0;
}