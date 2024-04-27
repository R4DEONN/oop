#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "ISolidShape.h"
#include "Point.h"

class Circle : public ISolidShape
{
public:
	Circle(Point center, double radius, uint32_t outlineColor, uint32_t fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	std::string ToString() const override;

	Point GetCenter() const;
	double GetRadius() const;

private:
	Point m_center;
	double m_radius;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};


#endif //_CIRCLE_H
