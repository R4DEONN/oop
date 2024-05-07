#include "Shape.h"
#include "utils.h"

Shape::Shape(uint32_t outlineColor)
: m_outlineColor(outlineColor)
{

}

std::string Shape::ToString() const
{
	return "Square: " + toStringWithPrecision(GetArea()) + "\n" +
		   "Perimeter: " + toStringWithPrecision(GetPerimeter()) + "\n" +
		   "Stroke color: " + toStringHex(GetOutlineColor()) + "\n";
}

uint32_t Shape::GetOutlineColor() const
{
	return m_outlineColor;
}
