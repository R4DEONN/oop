#ifndef _CANVAS_H
#define _CANVAS_H

#include "ICanvas.h"
#include "SFML/Graphics/RenderWindow.hpp"

class Canvas : public ICanvas
{
public:
	Canvas(sf::RenderTarget& m_renderTarget);
	void DrawLine(Point from, Point to, uint32_t lineColor) override;
	void FillPolygon(const std::vector<Point>& points, uint32_t fillColor) override;
	void DrawCircle(Point center, double radius, uint32_t lineColor) override;
	void FillCircle(Point center, double radius, uint32_t fillColor) override;
private:
	sf::RenderTarget& m_renderTarget;
};

#endif //_CANVAS_H
