#ifndef _FIGURECOLLECTIONCONTROLLER_H
#define _FIGURECOLLECTIONCONTROLLER_H

#include <functional>
#include "iostream"
#include "FigureCollection.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "LineSegment.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <map>
#include <regex>

class FigureCollectionController
{
public:
	FigureCollectionController(FigureCollection& figureCollection, std::istream& input, std::ostream& output);
	bool HandleCommand();
	void PrintFigureWithMaxSquare() const;
	void PrintFigureWithMinPerimeter() const;
	void DrawShapes(sf::RenderWindow& window) const;

private:
	using Handler = std::function<void(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	FigureCollection& m_figureCollection;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;

	RectangleData ParseRectangleData(const std::smatch& matches);
	void ReadRectangle(std::istream& args);
	TriangleData ParseTriangleData(const std::smatch& matches);
	void ReadTriangle(std::istream& args);
	CircleData ParseCircleData(const std::smatch& matches);
	void ReadCircle(std::istream& args);
	LineSegmentData ParseLineData(const std::smatch& matches);
	void ReadLine(std::istream& args);

	std::smatch ValidateAndExtractShapeDeclaration(const std::string& argsStr, const std::regex& pattern);
};


#endif //_FIGURECOLLECTIONCONTROLLER_H
