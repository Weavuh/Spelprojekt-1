#ifndef INCLUDED_SETTINGSTATE
#define INCLUDED_SETTINGSTATE

#include <SFML\Graphics.hpp>
#include "GameState.h"

class SettingState : public GameState {
public:
	SettingState(GameStateManager* gsm);
	virtual void init();
	virtual void update();
	virtual void draw(sf::RenderWindow* window);
	virtual void handleInputs(sf::Event* events);
protected:
	GameStateManager* gsm;
private:
	int selection;
	int pointerY;
	int pointerX;
};

#endif