#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "SolidShape.h"
#include "Point.h"

struct TriangleData
{
	Point firstPoint;
	Point secondPoint;
	Point thirdPoint;
	uint32_t outlineColor;
	uint32_t fillColor;
};

class Triangle : public SolidShape
{
public:
	Triangle(Point firstPoint, Point secondPoint, Point thirdPoint, uint32_t outlineColor, uint32_t fillColor);
	explicit Triangle(TriangleData triangleData);
	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;

	void Draw(ICanvas &canvas) const override;

private:
	Point m_firstPoint;
	Point m_secondPoint;
	Point m_thirdPoint;
};


#endif //_TRIANGLE_H
