#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "ISolidShape.h"
#include "Point.h"

class Triangle : public ISolidShape
{
public:
	Triangle(Point firstPoint, Point secondPoint, Point thirdPoint, uint32_t outlineColor, uint32_t fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	std::string ToString() const override;


private:
	Point m_firstPoint;
	Point m_secondPoint;
	Point m_thirdPoint;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};


#endif //_TRIANGLE_H
