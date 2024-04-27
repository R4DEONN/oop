#ifndef _LINESEGMENT_H
#define _LINESEGMENT_H

#include "IShape.h"
#include "Point.h"
#include <cmath>

class LineSegment : public IShape
{
public:
	LineSegment(Point startPoint, Point endPoint);
	LineSegment(Point startPoint, Point endPoint, uint32_t outlineColor);
	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	std::string ToString() const override;

	Point GetStartPoint() const;
	Point GetEndPoint() const;

private:
	Point m_startPoint;
	Point m_endPoint;
	uint32_t m_outlineColor = std::numeric_limits<uint32_t>::quiet_NaN();
};


#endif //_LINESEGMENT_H
