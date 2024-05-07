#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "SolidShape.h"
#include "Point.h"

struct CircleData
{
	Point center;
	double radius;
	uint32_t outlineColor;
	uint32_t fillColor;
};

class Circle : public SolidShape
{
public:
	Circle(Point center, double radius, uint32_t outlineColor, uint32_t fillColor);

	explicit Circle(CircleData circleData);

	double GetArea() const override;

	double GetPerimeter() const override;

	Point GetCenter() const;

	double GetRadius() const;

	void Draw(ICanvas &canvas) const override;

private:
	Point m_center;
	double m_radius;
};


#endif //_CIRCLE_H
