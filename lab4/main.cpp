#include "FigureCollectionController.h"
#include <SFML/Graphics.hpp>

void CreateWindow(sf::RenderWindow& window)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(
		{1800, 1200},
		"Journey of the Prairie King", sf::Style::Default, settings);
	window.clear(sf::Color::White);
}

void HandleEvents(sf::RenderWindow& window)
{
	sf::Event event{};
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

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