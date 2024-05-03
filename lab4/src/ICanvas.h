#ifndef _ICANVAS_H
#define _ICANVAS_H

#include <cstdint>
#include <vector>
#include "Point.h"

class ICanvas
{
public:
	virtual void DrawLine(Point from, Point to, uint32_t lineColor) = 0;
	virtual void FillPolygon(std::vector<Point> points, uint32_t fillColor) = 0;
	virtual void DrawCircle(Point center, double radius, uint32_t lineColor) = 0;
	virtual void FillCircle(Point center, double radius, uint32_t fillColor) = 0;
protected:
	~ICanvas() = default;
};


#endif //_ICANVAS_H
