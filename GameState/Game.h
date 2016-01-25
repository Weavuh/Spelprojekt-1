#ifndef INCLUDED_GAME
#define INCLUDED_GAME

#include <SFML\Graphics.hpp>
#include "GameStateManager.h"

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void update();
	void draw();
	sf::RenderWindow window;
	GameStateManager* gsm;
};

#endif