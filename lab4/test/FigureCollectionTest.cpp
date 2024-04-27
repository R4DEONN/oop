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

	std::string expectedOutput =
		"Max square figure\n"
		"Square: 1240.28\n"
		"Perimeter: 142.20\n"
		"Stroke color: ff0000\n"
		"Fill color: 00ff00\n"

		"Min perimeter figure\n"
		"Square: 1240.28\n"
		"Perimeter: 142.20\n"
		"Stroke color: ff0000\n"
		"Fill color: 00ff00\n";

	REQUIRE(expectedOutput == output.str());
}
//
//TEST_CASE("Four figure")
//{
//	FigureCollection figureCollection;
//
//	std::istringstream input(
//		"rectangle 10.3 20.15 1 1 ff0000 00ff00\n"
//		"line 0 0 1000 0 ff000f\n"
//		"triangle 0 0 12 0 0 5 ff0010 f0ff00\n"
//		"circle 10.3 20.15 2 ff0000 f0ff00\n"
//		);
//	std::ostringstream output;
//
//	FigureCollectionController figureCollectionController(figureCollection, input, output);
//	HandleCommands(figureCollectionController, input);
//
//	std::string expectedOutput =
//		"Max square figure\n"
//		"Square: 30.00\n"
//		"Perimeter: 30.00\n"
//		"Stroke color: ff0010\n"
//		"Fill color: f0ff00\n"
//
//		"Min perimeter figure\n"
//		"Square: 0.00\n"
//		"Perimeter: 1000.00\n"
//		"Stroke color: ff000f\n";
//
//	REQUIRE(expectedOutput == output.str());
//}
//
//TEST_CASE("PrintFigureWithMaxSquare")
//{
//	FigureCollection figureCollection;
//
//	std::istringstream input("rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00");
//	std::ostringstream output;
//
//	FigureCollectionController figureCollectionController(figureCollection, input, output);
//	HandleCommands(figureCollectionController, input);
//
//	std::string expectedOutput =
//		"Max square figure\n"
//		"Square: 1240.28\n"
//		"Perimeter: 142.20\n"
//		"Stroke color: ff0000\n"
//		"Fill color: 00ff00\n"
//
//		"Min perimeter figure\n"
//		"Square: 1240.28\n"
//		"Perimeter: 142.20\n"
//		"Stroke color: ff0000\n"
//		"Fill color: 00ff00\n";
//
//	REQUIRE(expectedOutput == output.str());
//}