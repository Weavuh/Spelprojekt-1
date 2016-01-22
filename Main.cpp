#include <SFML/Graphics.hpp>

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Fullscreen, settings);
	sf::RectangleShape shape(sf::Vector2f(300, 150));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(500, 500);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		shape.move(sf::Vector2f(0.1, 0));
		shape.rotate(0.1);
		shape.scale(1.001, 1.001);

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}