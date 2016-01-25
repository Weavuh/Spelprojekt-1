#ifndef INCLUDED_GAMESTATE
#define INCLUDED_GAMESTATE

#include <SFML\Graphics.hpp>
#include "GameStateManager.h"

class GameState {
public:
	GameState();
	~GameState();
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow* window) = 0;
	virtual void handleInputs(sf::Event* events) = 0;
};

#endif