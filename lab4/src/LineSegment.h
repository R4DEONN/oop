#ifndef _LINESEGMENT_H
#define _LINESEGMENT_H

#include "IShape.h"
#include "Point.h"
#include <cmath>

struct LineSegmentData
{
	Point startPoint;
	Point endPoint;
	uint32_t outlineColor;
};

class LineSegment : public IShape
{
public:
	LineSegment(Point startPoint, Point endPoint, uint32_t outlineColor);
	explicit LineSegment(LineSegmentData lineSegmentData);
	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] std::string ToString() const override;

	[[nodiscard]] Point GetStartPoint() const;
	[[nodiscard]] Point GetEndPoint() const;

	void Draw(ICanvas &canvas) override;

private:
	Point m_startPoint;
	Point m_endPoint;
	uint32_t m_outlineColor = std::numeric_limits<uint32_t>::quiet_NaN();
};


#endif //_LINESEGMENT_H
