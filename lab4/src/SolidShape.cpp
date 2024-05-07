#include "SolidShape.h"
#include "utils.h"

SolidShape::SolidShape(uint32_t outlineColor, uint32_t fillColor)
	: Shape(outlineColor),
	  m_fillColor(fillColor)
{

}

uint32_t SolidShape::GetFillColor() const
{
	return m_fillColor;
}

std::string SolidShape::ToString() const
{
	return Shape::ToString() + "Fill color: " + toStringHex(GetFillColor()) + "\n";
}
