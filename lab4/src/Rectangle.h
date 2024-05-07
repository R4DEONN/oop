#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "Point.h"
#include "SolidShape.h"

struct RectangleData
{
	Point leftTopPoint;
	double width;
	double height;
	uint32_t outlineColor;
	uint32_t fillColor;
};

class Rectangle : public SolidShape
{
public:
	Rectangle(Point leftTopPoint, double width, double height, uint32_t outlineColor, uint32_t fillColor);
	explicit Rectangle(RectangleData rectangleData);
	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;

	[[nodiscard]] Point GetLeftTop() const;
	[[nodiscard]] Point GetRightBottom() const;
	[[nodiscard]] double GetWidth() const;
	[[nodiscard]] double GetHeight() const;

	void Draw(ICanvas &canvas) const override;
private:
	Point m_leftTop;
	double m_width;
	double m_height;
};


#endif //_RECTANGLE_H
