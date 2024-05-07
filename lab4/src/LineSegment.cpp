#include "LineSegment.h"
#include "utils.h"

LineSegment::LineSegment(Point startPoint, Point endPoint, uint32_t outlineColor)
	: Shape(outlineColor),
	  m_startPoint(startPoint),
	  m_endPoint(endPoint)
{
}

LineSegment::LineSegment(LineSegmentData lineSegmentData)
	: Shape(lineSegmentData.outlineColor),
	  m_startPoint(lineSegmentData.startPoint),
	  m_endPoint(lineSegmentData.endPoint)
{

}

double LineSegment::GetArea() const
{
	return 0;
}

double LineSegment::GetPerimeter() const
{
	return GetDistance(m_startPoint, m_endPoint);
}

Point LineSegment::GetStartPoint() const
{
	return m_startPoint;
}

Point LineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void LineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}
