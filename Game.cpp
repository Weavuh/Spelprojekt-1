#include "Game.h"

Game::Game() :
window(sf::RenderWindow(sf::VideoMode(1920, 1080), "Strigiformes", sf::Style::Close))
{
	gsm = new GameStateManager();
}

Game::~Game() 
{
}

void Game::run() 
{
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		while (accumulator > ups)
		{
			accumulator -= ups;

			update();

			window.clear();
			draw();
			window.display();
		}

		accumulator += clock.restart();
	}
}

void Game::update() 
{
	gsm->update();
}

void Game::draw()
{
	gsm->draw(&window);
}