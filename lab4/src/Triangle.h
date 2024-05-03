#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "ISolidShape.h"
#include "Point.h"

struct TriangleData
{
	Point firstPoint;
	Point secondPoint;
	Point thirdPoint;
	uint32_t outlineColor;
	uint32_t fillColor;
};

class Triangle : public ISolidShape
{
public:
	Triangle(Point firstPoint, Point secondPoint, Point thirdPoint, uint32_t outlineColor, uint32_t fillColor);
	explicit Triangle(TriangleData triangleData);
	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;
	[[nodiscard]] std::string ToString() const override;

	void Draw(ICanvas &canvas) override;

private:
	Point m_firstPoint;
	Point m_secondPoint;
	Point m_thirdPoint;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};


#endif //_TRIANGLE_H
