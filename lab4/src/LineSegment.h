#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include "IShape.h"
#include "Point.h"
#include "Shape.h"
#include <cmath>

struct LineSegmentData
{
	Point startPoint;
	Point endPoint;
	uint32_t outlineColor;
};

class LineSegment : public Shape
{
public:
	LineSegment(Point startPoint, Point endPoint, uint32_t outlineColor);
	explicit LineSegment(LineSegmentData lineSegmentData);
	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;

	[[nodiscard]] Point GetStartPoint() const;
	[[nodiscard]] Point GetEndPoint() const;

	void Draw(ICanvas &canvas) const override;

private:
	Point m_startPoint;
	Point m_endPoint;
	uint32_t m_outlineColor = std::numeric_limits<uint32_t>::quiet_NaN();
};


#endif //LINESEGMENT_H
