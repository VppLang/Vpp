 
#include "vppMath.h"

double vppMath::pythagorasTheorem(double a, double b)
{
	return sqrt(pow(a, 2) + pow(b, 2));
}

float vppMath::squareArea(float side)
{
	return pow(side,2);
}

float vppMath::parallelogramArea(float b, float h)
{
	return b * h;
}

float vppMath::rectangleArea(float length, float width)
{
	return length * width;
}

float vppMath::triangleArea(float base, float height)
{
	return (base * height) / 2;
}

float vppMath::trapezoidArea(float base1, float base2, float height)
{
	return height / 2  * (base1 + base2);
}

double vppMath::circleArea(int radius)
{
	return pi * pow(radius, 2);
}

double vppMath::ellipseArea(int radius1, int radius2)
{
	return pi * pow(radius1, 2) * pow(radius2, 2);
}

 

Vector2d vppMath::normalize(Vector2d vectorToNormalize)
{
	return Vector2d(vectorToNormalize.x / sqrt(pow(vectorToNormalize.x, 2) + pow(vectorToNormalize.y, 2)), vectorToNormalize.y / sqrt(pow(vectorToNormalize.x, 2) + pow(vectorToNormalize.y, 2)));
}

Vector2d vppMath::normalize(float x, float y)
{
	return Vector2d(x / sqrt(pow(x, 2) + pow(y, 2)), y / sqrt(pow(x, 2) + pow(y, 2)));

}

std::vector<float> vppMath::bubbleSort(std::vector<float> a)
{

	bool notSorted = false;
	size_t lastSorted = a.size() - 1;

	int swaps = 0;
	while (!notSorted) {
		notSorted = true;
		for (int i = 0; i < lastSorted; i++) {
			if (a[i] > a[i + 1]) {
				swaps++;
				std::swap(a[i], a[i + 1]);
				notSorted = false;
			}

		}
		lastSorted--;
	}
	std::vector<float> aa;
	aa = a;
	return aa;
}

 

constexpr double vppMath::rad_to_degree(float radian)
{
		return radian * (180.f /  this->pi);

}
