#include "Rectangle.h"

Rectangle::Rectangle(Point leftTopPoint, double width, double height, uint32_t outlineColor, uint32_t fillColor)
	: SolidShape(outlineColor, fillColor),
	  m_leftTop(leftTopPoint),
	  m_width(width),
	  m_height(height)
{

}

Rectangle::Rectangle(RectangleData rectangleData)
	: SolidShape(rectangleData.outlineColor, rectangleData.fillColor),
	  m_leftTop(rectangleData.leftTopPoint),
	  m_width(rectangleData.width),
	  m_height(rectangleData.height)
{

}

double Rectangle::GetArea() const
{
	return m_width * m_height;
}

double Rectangle::GetPerimeter() const
{
	return m_width * 2 + m_height * 2;
}

Point Rectangle::GetLeftTop() const
{
	return m_leftTop;
}

Point Rectangle::GetRightBottom() const
{
	return { m_leftTop.x + m_width, m_leftTop.y + m_height };
}

double Rectangle::GetWidth() const
{
	return m_width;
}

double Rectangle::GetHeight() const
{
	return m_height;
}

void Rectangle::Draw(ICanvas& canvas) const
{
	canvas.FillPolygon({
		m_leftTop,
		{ m_leftTop.x, m_leftTop.y + m_height },
		{ m_leftTop.x + m_width, m_leftTop.y + m_height },
		{ m_leftTop.x + m_width, m_leftTop.y }
	}, SolidShape::GetFillColor());
}
