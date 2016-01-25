#ifndef INCLUDED_MENUSTATE
#define INCLUDED_MENUSTATE

#include <SFML\Graphics.hpp>
#include "GameState.h"

class MenuState : public GameState {
public:
	MenuState(GameStateManager* gsm);
	virtual void init();
	virtual void update();
	virtual void draw(sf::RenderWindow* window);
protected:
	GameStateManager* gsm;
private:
	int selection;
};

#endif