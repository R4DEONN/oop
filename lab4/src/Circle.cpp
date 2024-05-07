#include "Circle.h"
#include "cmath"

Circle::Circle(Point center, double radius, uint32_t outlineColor, uint32_t fillColor)
	: SolidShape(outlineColor, fillColor),
	m_center(center),
	  m_radius(radius)
{

}

Circle::Circle(CircleData circleData)
	: SolidShape(circleData.outlineColor, circleData.fillColor),
	  m_center(circleData.center),
	  m_radius(circleData.radius)
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

Point Circle::GetCenter() const
{
	return m_center;
}

double Circle::GetRadius() const
{
	return m_radius;
}

void Circle::Draw(ICanvas& canvas) const
{
	canvas.DrawCircle(m_center, m_radius, GetOutlineColor());
	canvas.FillCircle(m_center, m_radius, SolidShape::GetFillColor());
}

