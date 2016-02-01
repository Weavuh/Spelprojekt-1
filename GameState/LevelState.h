#ifndef INCLUDED_LEVELSTATE
#define INCLUDED_LEVELSTATE

#include "GameState.h"
#include "Player.h"
#include "Bunny.h"
#include "Shroom.h"
#include <vector>

using namespace std;
using namespace sf;

class LevelState : public GameState
{
public:
	LevelState(GameStateManager* gsm);
	virtual void init();
	virtual void update();
	virtual void draw(sf::RenderWindow* window);
	virtual void handleInputs(sf::Event* events);
	bool isOffScreen(Sprite sprite);
protected:
	GameStateManager* gsm;
private:
	Player* player;
	Bunny* bunny;
	Shroom* shroom;
	typedef vector<Sprite*> SpriteVector;
	SpriteVector ground;
	SpriteVector wall;
	SpriteVector ceiling;
	SpriteVector foreGround;
	View view;
	bool escape;
};

#endif
