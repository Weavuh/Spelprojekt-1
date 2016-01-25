#include "Game.h"

Game::Game() :
window(sf::RenderWindow(sf::VideoMode(1920, 1080), "Strigiformes", sf::Style::Close))
{
	window.setKeyRepeatEnabled(false);
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
		sf::Event events;
		while (window.pollEvent(events))
		{
			gsm->handleInputs(&events);
			if (events.type == sf::Event::Closed)
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