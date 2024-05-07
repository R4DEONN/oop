#include "catch2/catch_test_macros.hpp"
#include "FigureCollectionController.h"

void HandleCommands(FigureCollectionController& figureCollectionController, std::istream& input)
{
	while (!input.eof() && !input.fail())
	{
		figureCollectionController.HandleCommand();
	}
}

TEST_CASE("One rectangle")
{
	FigureCollection figureCollection;

	std::istringstream input("rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00");
	std::ostringstream output;

	FigureCollectionController figureCollectionController(figureCollection, input, output);
	HandleCommands(figureCollectionController, input);
	figureCollectionController.PrintFigureWithMaxSquare();
	figureCollectionController.PrintFigureWithMinPerimeter();

	std::string expectedOutput =
		"Max square figure\n"
		"Square: 1240.28\n"
		"Perimeter: 142.20\n"
		"Stroke color: ff0000\n"
		"Fill color: 00ff00\n"
		"\n"
		"Min perimeter figure\n"
		"Square: 1240.28\n"
		"Perimeter: 142.20\n"
		"Stroke color: ff0000\n"
		"Fill color: 00ff00\n\n";

	REQUIRE(expectedOutput == output.str());
}

TEST_CASE("One circle")
{
	FigureCollection figureCollection;

	std::istringstream input("circle 10.3 20.15 2 ff0000 f0ff00");
	std::ostringstream output;

	FigureCollectionController figureCollectionController(figureCollection, input, output);
	HandleCommands(figureCollectionController, input);
	figureCollectionController.PrintFigureWithMaxSquare();
	figureCollectionController.PrintFigureWithMinPerimeter();

	std::string expectedOutput =
		"Max square figure\n"
		"Square: 12.57\n"
		"Perimeter: 12.57\n"
		"Stroke color: ff0000\n"
		"Fill color: f0ff00\n"
		"\n"
		"Min perimeter figure\n"
		"Square: 12.57\n"
		"Perimeter: 12.57\n"
		"Stroke color: ff0000\n"
		"Fill color: f0ff00\n\n";

	REQUIRE(expectedOutput == output.str());
}

TEST_CASE("One triangle")
{
	FigureCollection figureCollection;

	std::istringstream input("triangle 0 0 12 0 0 5 ff0010 f0ff00");
	std::ostringstream output;

	FigureCollectionController figureCollectionController(figureCollection, input, output);
	HandleCommands(figureCollectionController, input);
	figureCollectionController.PrintFigureWithMaxSquare();
	figureCollectionController.PrintFigureWithMinPerimeter();

	std::string expectedOutput =
		"Max square figure\n"
		"Square: 30.00\n"
		"Perimeter: 30.00\n"
		"Stroke color: ff0010\n"
		"Fill color: f0ff00\n"
		"\n"
		"Min perimeter figure\n"
		"Square: 30.00\n"
		"Perimeter: 30.00\n"
		"Stroke color: ff0010\n"
		"Fill color: f0ff00\n\n";

	REQUIRE(expectedOutput == output.str());
}

TEST_CASE("One line")
{
	FigureCollection figureCollection;

	std::istringstream input("line 0 0 1000 0 ff000f");
	std::ostringstream output;

	FigureCollectionController figureCollectionController(figureCollection, input, output);
	HandleCommands(figureCollectionController, input);
	figureCollectionController.PrintFigureWithMaxSquare();
	figureCollectionController.PrintFigureWithMinPerimeter();

	std::string expectedOutput =
		"Max square figure\n"
		"Square: 0.00\n"
		"Perimeter: 1000.00\n"
		"Stroke color: ff000f\n"
		"\n"
		"Min perimeter figure\n"
		"Square: 0.00\n"
		"Perimeter: 1000.00\n"
		"Stroke color: ff000f\n\n";

	REQUIRE(expectedOutput == output.str());
}


TEST_CASE("Four figure")
{
	FigureCollection figureCollection;

	std::istringstream input(
		"rectangle 10.3 20.15 400 400 ff0000ff 00ff00ff\n"
		"line 0 0 1000 0 ff000fff\n"
		"triangle 0 0 100 0 0 300 ff0010ff f0ff00ff\n"
		"circle 10.3 20.15 500 ff0000ff f0ff00ff\n"
		);
	std::ostringstream output;

	FigureCollectionController figureCollectionController(figureCollection, input, output);
	HandleCommands(figureCollectionController, input);
	figureCollectionController.PrintFigureWithMaxSquare();
	figureCollectionController.PrintFigureWithMinPerimeter();

	std::string expectedOutput =
		"Max square figure\n"
		"Square: 785398.16\n"
		"Perimeter: 3141.59\n"
		"Stroke color: ff0000ff\n"
		"Fill color: f0ff00ff\n\n"

		"Min perimeter figure\n"
		"Square: 15000.00\n"
		"Perimeter: 716.23\n"
		"Stroke color: ff0010ff\n"
		"Fill color: f0ff00ff\n\n";

	REQUIRE(expectedOutput == output.str());
}

//TODO: Draw выводить в Output вызовы canvas