#include "FigureCollectionController.h"

int main()
{
	FigureCollection figureCollection;
	FigureCollectionController figureCollectionController(figureCollection, std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		if (!figureCollectionController.HandleCommand())
		{
			std::cout << "Unknown command" << std::endl;
		}
	}

	figureCollectionController.PrintFigureWithMaxSquare();
	figureCollectionController.PrintFigureWithMinPerimeter();

	return EXIT_SUCCESS;
}