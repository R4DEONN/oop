#include "FigureCollectionController.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Canvas.h"
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
	m_figureCollection.EnumerateShapes([this](const std::vector<std::shared_ptr<IShape>>& shapes)
	{
		auto FigureWithMaxSquare = shapes[0];
		for (const auto& shape: shapes)
		{
			if (shape->GetArea() > FigureWithMaxSquare->GetArea())
			{
				FigureWithMaxSquare = shape;
			}
		}

		m_output << "Max square figure" << std::endl << FigureWithMaxSquare->ToString() << std::endl;
	});
}

void FigureCollectionController::PrintFigureWithMinPerimeter() const
{
	m_figureCollection.EnumerateShapes([this](const std::vector<std::shared_ptr<IShape>>& shapes)
	{
		auto FigureWithMinPerimeter = shapes[0];
		for (const auto& shape: shapes)
		{
			if (shape->GetPerimeter() < FigureWithMinPerimeter->GetPerimeter())
			{
				FigureWithMinPerimeter = shape;
			}
		}

		m_output << "Min perimeter figure" << std::endl << FigureWithMinPerimeter->ToString() << std::endl;
	});
}

void FigureCollectionController::ReadRectangle(std::istream& args)
{
	try
	{
		std::string argsStr;
		std::getline(args, argsStr); // Чтение строки из входного потока

		std::regex pattern(R"(\s+(-?\d+.?\d*)\s+(-?\d+.?\d*)\s+(\d+.?\d*)\s+(\d+.?\d*)\s+(\w+)\s+(\w+))");
		std::smatch matches = ValidateAndExtractShapeDeclaration(argsStr, pattern);

		RectangleData rectangleData = ParseRectangleData(matches);
		auto rectangle = std::make_shared<Rectangle>(rectangleData);
		m_figureCollection.Insert(rectangle);
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

TriangleData FigureCollectionController::ParseTriangleData(const std::smatch& matches)
{
	TriangleData triangleData{};

	Point firstPoint(std::stod(matches[1]), std::stod(matches[2]));
	triangleData.firstPoint = firstPoint;
	Point secondPoint(std::stod(matches[3]), std::stod(matches[4]));
	triangleData.secondPoint = secondPoint;
	Point thirdPoint(std::stod(matches[5]), std::stod(matches[6]));
	triangleData.thirdPoint = thirdPoint;
	triangleData.outlineColor = static_cast<uint32_t>(std::stoul(matches[7], nullptr, 16));
	triangleData.fillColor = static_cast<uint32_t>(std::stoul(matches[8], nullptr, 16));

	return triangleData;
}

void FigureCollectionController::ReadTriangle(std::istream& args)
{
	try
	{
		std::string argsStr;
		std::getline(args, argsStr); // Чтение строки из входного потока

		std::regex pattern(R"(\s+(-?\d+.?\d*)\s+(-?\d+.?\d*)\s+(-?\d+.?\d*)\s+(-?\d+.?\d*)\s+(-?\d+.?\d*)\s+(-?\d+.?\d*)\s+(\w+)\s+(\w+))");
		std::smatch matches = ValidateAndExtractShapeDeclaration(argsStr, pattern);

		auto triangleData = ParseTriangleData(matches);
		auto triangle = std::make_shared<Triangle>(triangleData);
		m_figureCollection.Insert(triangle);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void FigureCollectionController::ReadCircle(std::istream& args)
{
	try
	{
		std::string argsStr;
		std::getline(args, argsStr); // Чтение строки из входного потока

		std::regex pattern(R"(\s+(-?\d+.?\d*)\s+(-?\d+.?\d*)\s+(\d+.?\d*)\s+(\w+)\s+(\w+))");
		std::smatch matches = ValidateAndExtractShapeDeclaration(argsStr, pattern);

		auto circleData = ParseCircleData(matches);
		auto circle = std::make_shared<Circle>(circleData);
		m_figureCollection.Insert(circle);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

CircleData FigureCollectionController::ParseCircleData(const std::smatch& matches)
{
	CircleData circleData{};

	Point center(std::stod(matches[1]), std::stod(matches[2]));
	circleData.center = center;
	circleData.radius = std::stod(matches[3]);
	circleData.outlineColor = static_cast<uint32_t>(std::stoul(matches[4], nullptr, 16));
	circleData.fillColor = static_cast<uint32_t>(std::stoul(matches[5], nullptr, 16));

	return circleData;
}

void FigureCollectionController::ReadLine(std::istream& args)
{
	try
	{
		std::string argsStr;
		std::getline(args, argsStr); // Чтение строки из входного потока

		std::regex pattern(R"(\s+(-?\d+.?\d*)\s+(-?\d+.?\d*)\s+(-?\d+.?\d*)\s+(-?\d+.?\d*)\s+(\w+))");
		std::smatch matches = ValidateAndExtractShapeDeclaration(argsStr, pattern);

		auto lineData = ParseLineData(matches);
		auto line = std::make_shared<LineSegment>(lineData);
		m_figureCollection.Insert(line);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

LineSegmentData FigureCollectionController::ParseLineData(const std::smatch& matches)
{
	LineSegmentData lineData{};

	Point startPoint(std::stod(matches[1]), std::stod(matches[2]));
	lineData.startPoint = startPoint;
	Point endPoint(std::stod(matches[3]), std::stod(matches[4]));
	lineData.endPoint = endPoint;
	lineData.outlineColor = static_cast<uint32_t>(std::stoul(matches[5], nullptr, 16));

	return lineData;
}

std::smatch FigureCollectionController::ValidateAndExtractShapeDeclaration(
	const std::string& argsStr,
	const std::regex& pattern
)
{
	std::smatch matches;

	if (!std::regex_match(argsStr, matches, pattern))
	{
		throw std::invalid_argument("Incorrect syntax of shape declaration");
	}

	return matches;
}

void FigureCollectionController::DrawShapes(sf::RenderWindow& window) const
{
	Canvas canvas(window);
	m_figureCollection.EnumerateShapes([&](const std::vector<std::shared_ptr<IShape>>& shapes)
	{
		for (const auto& shape: shapes)
		{
			shape->Draw(canvas);
		}
	});
}

