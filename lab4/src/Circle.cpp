#include "Circle.h"
#include "cmath"
#include "utils.h"

Circle::Circle(Point center, double radius, uint32_t outlineColor, uint32_t fillColor)
	: m_center(center),
	  m_radius(radius),
	  m_outlineColor(outlineColor),
	  m_fillColor(fillColor)
{

}

double Circle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double Circle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

uint32_t Circle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Circle::GetFillColor() const
{
	return m_fillColor;
}

Point Circle::GetCenter() const
{
	return m_center;
}

double Circle::GetRadius() const
{
	return m_radius;
}

std::string Circle::ToString() const
{
	std::string info;
	return "Square: " + toStringWithPrecision(GetArea()) + "\n" +
		   "Perimeter: " + toStringWithPrecision(GetPerimeter()) + "\n" +
		   "Stroke color: " + toStringHex(GetOutlineColor()) + "\n" +
		   "Fill color: " + toStringHex(GetFillColor()) + "\n";
}

