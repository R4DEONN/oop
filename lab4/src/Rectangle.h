#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "ISolidShape.h"
#include "Point.h"

struct RectangleData
{
	Point leftTopPoint;
	double width;
	double height;
	uint32_t outlineColor;
	uint32_t fillColor;
};

class Rectangle : public ISolidShape
{
public:
	Rectangle(Point leftTopPoint, double width, double height, uint32_t outlineColor, uint32_t fillColor);
	explicit Rectangle(RectangleData rectangleData);
	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;
	[[nodiscard]] std::string ToString() const override;

	[[nodiscard]] Point GetLeftTop() const;
	[[nodiscard]] Point GetRightBottom() const;
	[[nodiscard]] double GetWidth() const;
	[[nodiscard]] double GetHeight() const;
private:
	Point m_leftTop;
	Point m_rightBottom;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
	double m_width;
	double m_height;
};


#endif //_RECTANGLE_H
