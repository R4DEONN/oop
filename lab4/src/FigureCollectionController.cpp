#include "FigureCollectionController.h"
#include "Rectangle.h"
#include <sstream>
#include <regex>

FigureCollectionController::FigureCollectionController(FigureCollection& figureCollection, std::istream& input,
	std::ostream& output)
	: m_figureCollection(figureCollection),
	  m_input(input),
	  m_output(output),
	  m_actionMap({
		  { "rectangle", [this](std::istream& strm)
						 { ReadRectangle(strm); }},
		  { "circle",    [this](std::istream& strm)
						 { ReadCircle(strm); }},
		  { "triangle",  [this](std::istream& strm)
						 { ReadTriangle(strm); }},
		  { "line",      [this](std::istream& strm)
						 { ReadLine(strm); }},
	  })
{

}

bool FigureCollectionController::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	if (commandLine.empty())
	{
		return true;
	}
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
		return true;
	}

	return false;
}

void FigureCollectionController::PrintFigureWithMaxSquare() const
{
	m_figureCollection.EnumerateShapes([this](const std::vector<IShape*>& shapes)
	{
		IShape* FigureWithMaxSquare = shapes[0];
		for (const auto& shape: shapes)
		{
			if (shape->GetArea() > FigureWithMaxSquare->GetArea())
			{
				FigureWithMaxSquare = shape;
			}
		}

		m_output << FigureWithMaxSquare->ToString() << std::endl;
	});
}

void FigureCollectionController::PrintFigureWithMinPerimeter() const
{
	m_figureCollection.EnumerateShapes([this](const std::vector<IShape*>& shapes)
	{
		IShape* FigureWithMinPerimeter = shapes[0];
		for (const auto& shape: shapes)
		{
			if (shape->GetPerimeter() < FigureWithMinPerimeter->GetPerimeter())
			{
				FigureWithMinPerimeter = shape;
			}
		}

		m_output << FigureWithMinPerimeter << std::endl;
	});
}

void FigureCollectionController::ReadRectangle(std::istream& args)
{
	try
	{
		std::string argsStr;
		std::getline(args, argsStr); // Чтение строки из входного потока

		std::regex pattern(R"(\s+(\d+.?\d+)\s+(\d+.?\d+)\s+(\d+.?\d+)\s+(\d+.?\d+)\s+(\w+)\s+(\w+))");
		std::smatch matches;

		if (!std::regex_match(argsStr, matches, pattern))
		{
			throw std::invalid_argument("Incorrect syntax of function declaration");
		}

		RectangleData rectangleData = ParseRectangleData(matches);
		Rectangle rectangle{ rectangleData };
		m_figureCollection.Insert(&rectangle);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

RectangleData FigureCollectionController::ParseRectangleData(const std::smatch& matches)
{
	RectangleData rectangleData{};

	Point leftTop(std::stod(matches[1]), std::stod(matches[2]));
	rectangleData.leftTopPoint = leftTop;
	rectangleData.width = std::stod(matches[3]);
	rectangleData.height = std::stod(matches[4]);
	rectangleData.outlineColor = static_cast<uint32_t>(std::stoul(matches[5], nullptr, 16));
	rectangleData.fillColor = static_cast<uint32_t>(std::stoul(matches[6], nullptr, 16));

	return rectangleData;
}

void FigureCollectionController::ReadTriangle(std::istream& args)
{

}

void FigureCollectionController::ReadCircle(std::istream& args)
{

}

void FigureCollectionController::ReadLine(std::istream& args)
{

}

