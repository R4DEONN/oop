#ifndef _FIGURECOLLECTIONCONTROLLER_H
#define _FIGURECOLLECTIONCONTROLLER_H

#include <functional>
#include "iostream"
#include "FigureCollection.h"
#include "Rectangle.h"
#include <map>
#include <regex>

class FigureCollectionController
{
public:
	FigureCollectionController(FigureCollection& figureCollection, std::istream& input, std::ostream& output);
	bool HandleCommand();
	void PrintFigureWithMaxSquare() const;
	void PrintFigureWithMinPerimeter() const;

private:
	using Handler = std::function<void(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	FigureCollection& m_figureCollection;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;

	RectangleData ParseRectangleData(const std::smatch& matches);
	void ReadRectangle(std::istream& args);
	void ReadTriangle(std::istream& args);
	void ReadCircle(std::istream& args);
	void ReadLine(std::istream& args);
};


#endif //_FIGURECOLLECTIONCONTROLLER_H
