#include "LineSegment.h"
#include "utils.h"
#include <cmath>

LineSegment::LineSegment(Point startPoint, Point endPoint)
	: m_startPoint(startPoint),
	  m_endPoint(endPoint)
{
}

LineSegment::LineSegment(Point startPoint, Point endPoint, uint32_t outlineColor)
	: m_startPoint(startPoint),
	  m_endPoint(endPoint),
	  m_outlineColor(outlineColor)
{
}


double LineSegment::GetArea() const
{
	return 0;
}

double LineSegment::GetPerimeter() const
{
	return std::sqrt(
		std::pow((m_startPoint.x - m_endPoint.x), 2)
		+ std::pow((m_startPoint.y - m_endPoint.y), 2)
	);
}

uint32_t LineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string LineSegment::ToString() const
{
	std::string info =
		"Square: " + toStringWithPrecision(GetArea()) + "\n" +
		"Perimeter: " + toStringWithPrecision(GetPerimeter()) + "\n";

	if (m_outlineColor)
	{
		info += "Stroke color: " + toStringHex(GetOutlineColor()) + "\n";
	}
	return info;
}