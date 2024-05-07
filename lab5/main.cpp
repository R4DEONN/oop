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
	figureCollectionController.HandleCommand();

	figureCollectionController.PrintFigureWithMaxSquare();
	figureCollectionController.PrintFigureWithMinPerimeter();

	sf::RenderWindow window;
	CreateWindow(window);
	figureCollectionController.DrawShapes(window);
	window.display();

	while (window.isOpen())
	{
		HandleEvents(window);
		window.clear(sf::Color::White);
		figureCollectionController.DrawShapes(window);
		window.display();
	}

	return EXIT_SUCCESS;
}