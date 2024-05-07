#include "Triangle.h"
#include "utils.h"

Triangle::Triangle(Point firstPoint, Point secondPoint, Point thirdPoint, uint32_t outlineColor, uint32_t fillColor)
	: SolidShape(outlineColor, fillColor),
	  m_firstPoint(firstPoint),
	  m_secondPoint(secondPoint),
	  m_thirdPoint(thirdPoint)
{

}

Triangle::Triangle(TriangleData triangleData)
	: SolidShape(triangleData.outlineColor, triangleData.fillColor),
	m_firstPoint(triangleData.firstPoint),
	  m_secondPoint(triangleData.secondPoint),
	  m_thirdPoint(triangleData.thirdPoint)
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
	auto firstLinePerimeter = GetDistance(m_firstPoint, m_secondPoint);
	auto secondLinePerimeter = GetDistance(m_secondPoint, m_thirdPoint);
	auto thirdLinePerimeter = GetDistance(m_thirdPoint, m_firstPoint);
	return firstLinePerimeter + secondLinePerimeter + thirdLinePerimeter;
}

void Triangle::Draw(ICanvas& canvas) const
{
	canvas.FillPolygon({ m_firstPoint, m_secondPoint, m_thirdPoint }, SolidShape::GetFillColor());
}
