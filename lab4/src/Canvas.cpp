#include "Canvas.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/ConvexShape.hpp"

Canvas::Canvas(sf::RenderTarget& renderTarget)
: m_renderTarget(renderTarget)
{

}


void Canvas::DrawLine(Point from, Point to, uint32_t lineColor)
{
	sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(from.x, from.y), sf::Color(lineColor)),
			sf::Vertex(sf::Vector2f(to.x, to.y), sf::Color(lineColor))
		};

	m_renderTarget.draw(line, 2, sf::Lines);
}

void Canvas::FillPolygon(const std::vector<Point>& points, uint32_t fillColor)
{
	sf::ConvexShape convex;

	convex.setPointCount(points.size());

	for (size_t i = 0; i < points.size(); i++)
	{
		auto point = points[i];
		convex.setPoint(i, sf::Vector2f(point.x, point.y));
	}

	convex.setFillColor(sf::Color(fillColor));

	m_renderTarget.draw(convex);
}

void Canvas::DrawCircle(Point center, double radius, uint32_t lineColor)
{
	sf::CircleShape shape(radius, 60);
	shape.setOrigin(radius, radius);
	shape.setPosition(center.x, center.y);
	shape.setOutlineColor(sf::Color(lineColor));
	m_renderTarget.draw(shape);
}

void Canvas::FillCircle(Point center, double radius, uint32_t fillColor)
{
	sf::CircleShape shape(radius, 60);
	shape.setOrigin(radius, radius);
	shape.setPosition(center.x, center.y);
	shape.setFillColor(sf::Color(fillColor));
	m_renderTarget.draw(shape);
}