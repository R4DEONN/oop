#include "Triangle.h"
#include "LineSegment.h"
#include "utils.h"

Triangle::Triangle(Point firstPoint, Point secondPoint, Point thirdPoint, uint32_t outlineColor, uint32_t fillColor)
	: m_firstPoint(firstPoint),
	  m_secondPoint(secondPoint),
	  m_thirdPoint(thirdPoint),
	  m_outlineColor(outlineColor),
	  m_fillColor(fillColor)
{

}

Triangle::Triangle(TriangleData triangleData)
	: m_firstPoint(triangleData.firstPoint),
	  m_secondPoint(triangleData.secondPoint),
	  m_thirdPoint(triangleData.thirdPoint),
	  m_outlineColor(triangleData.outlineColor),
	  m_fillColor(triangleData.fillColor)
{

}


double Triangle::GetArea() const
{
	return 0.5 * std::abs(
		(m_firstPoint.x * (m_secondPoint.y - m_thirdPoint.y)) +
		(m_secondPoint.x * (m_thirdPoint.y - m_firstPoint.y)) +
		(m_thirdPoint.x * (m_firstPoint.y - m_secondPoint.y))
	);
}

double Triangle::GetPerimeter() const
{
	auto firstLine = LineSegment(m_firstPoint, m_secondPoint, 0);
	auto secondLine = LineSegment(m_secondPoint, m_thirdPoint, 0);
	auto thirdLine = LineSegment(m_thirdPoint, m_firstPoint, 0);
	return firstLine.GetPerimeter() + secondLine.GetPerimeter() + thirdLine.GetPerimeter();
}

uint32_t Triangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Triangle::GetFillColor() const
{
	return m_fillColor;
}

std::string Triangle::ToString() const
{
	return "Square: " + toStringWithPrecision(GetArea()) + "\n" +
		   "Perimeter: " + toStringWithPrecision(GetPerimeter()) + "\n" +
		   "Stroke color: " + toStringHex(GetOutlineColor()) + "\n" +
		   "Fill color: " + toStringHex(GetFillColor()) + "\n";
}

void Triangle::Draw(ICanvas& canvas)
{
	canvas.FillPolygon({m_firstPoint, m_secondPoint, m_thirdPoint}, m_fillColor);
}
