#include "Rectangle.h"
#include "utils.h"

Rectangle::Rectangle(Point leftTopPoint, double width, double height, uint32_t outlineColor, uint32_t fillColor)
: m_leftTop(leftTopPoint),
m_width(width),
m_height(height),
m_outlineColor(outlineColor),
m_fillColor(fillColor),
m_rightBottom({leftTopPoint.x + width, leftTopPoint.y + height}),
m_rightTop({leftTopPoint.x + width, leftTopPoint.y}),
m_leftBottom({leftTopPoint.x, leftTopPoint.y + height})
{

}

Rectangle::Rectangle(RectangleData rectangleData)
	: m_leftTop(rectangleData.leftTopPoint),
	  m_width(rectangleData.width),
	  m_height(rectangleData.height),
	  m_outlineColor(rectangleData.outlineColor),
	  m_fillColor(rectangleData.fillColor),
	  m_rightBottom({
		  rectangleData.leftTopPoint.x + rectangleData.width,
		  rectangleData.leftTopPoint.y + rectangleData.height
	  }),
	  m_rightTop({rectangleData.leftTopPoint.x + rectangleData.width, rectangleData.leftTopPoint.y}),
	  m_leftBottom({rectangleData.leftTopPoint.x, rectangleData.leftTopPoint.y + rectangleData.height})
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

uint32_t Rectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Rectangle::GetFillColor() const
{
	return m_fillColor;
}

Point Rectangle::GetLeftTop() const
{
	return m_leftTop;
}

Point Rectangle::GetRightBottom() const
{
	return m_rightBottom;
}

double Rectangle::GetWidth() const
{
	return m_width;
}

double Rectangle::GetHeight() const
{
	return m_height;
}

std::string Rectangle::ToString() const
{
	return "Square: " + toStringWithPrecision(GetArea()) + "\n" +
		   "Perimeter: " + toStringWithPrecision(GetPerimeter()) + "\n" +
		   "Stroke color: " + toStringHex(GetOutlineColor()) + "\n" +
		   "Fill color: " + toStringHex(GetFillColor()) + "\n";
}

void Rectangle::Draw(ICanvas& canvas)
{
	canvas.FillPolygon({
		m_leftTop,
		m_leftBottom,
		m_rightBottom,
		m_rightTop
	}, m_fillColor);
}
