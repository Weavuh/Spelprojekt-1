#ifndef INCLUDED_LEVELSTATE
#define INCLUDED_LEVELSTATE

#include "GameState.h"
#include "Player.h"

class LevelState : public GameState
{
public:
	LevelState(GameStateManager* gsm);
	virtual void init();
	virtual void update();
	virtual void draw(sf::RenderWindow* window);
	virtual void handleInputs(sf::Event* events);
protected:
	GameStateManager* gsm;
private:
	Player* player;
};

#endif
