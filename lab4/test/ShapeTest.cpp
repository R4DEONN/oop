#include "catch2/catch_test_macros.hpp"
#include "LineSegment.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

TEST_CASE("ReadLine to string")
{
	LineSegment lineSegment({0, 0}, {1000, 0}, 0xff000f);

	std::string expectedOutput =
		"Square: 0.00\n"
		"Perimeter: 1000.00\n"
		"Stroke color: ff000f\n";

	REQUIRE(expectedOutput == lineSegment.ToString());
}

TEST_CASE("ReadLine to string w/o outline")
{
	LineSegment lineSegment({0, 0}, {1000, 0});

	std::string expectedOutput =
		"Square: 0.00\n"
		"Perimeter: 1000.00\n";

	REQUIRE(expectedOutput == lineSegment.ToString());
}

TEST_CASE("ReadTriangle to string")
{
	Triangle triangle({0, 0}, {12, 0}, {0, 5}, 0xff0010, 0xf0ff00);

	std::string expectedOutput =
		"Square: 30.00\n"
		"Perimeter: 30.00\n"
		"Stroke color: ff0010\n"
		"Fill color: f0ff00\n";

	REQUIRE(expectedOutput == triangle.ToString());
}

TEST_CASE("Rectangle to string")
{
	Rectangle rectangle({50, 50}, 50, 10, 0x100000, 0xffffff);

	std::string expectedOutput =
		"Square: 500.00\n"
		"Perimeter: 120.00\n"
		"Stroke color: 100000\n"
		"Fill color: ffffff\n";

	REQUIRE(expectedOutput == rectangle.ToString());
}

TEST_CASE("ReadCircle to string")
{
	Circle circle({0, 0}, 10, 0x060050, 0x000000);

	std::string expectedOutput =
		"Square: 314.16\n"
		"Perimeter: 62.83\n"
		"Stroke color: 060050\n"
		"Fill color: 000000\n";

	REQUIRE(expectedOutput == circle.ToString());
}