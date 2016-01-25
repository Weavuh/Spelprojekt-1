#ifndef INCLUDED_GAMESTATEMANAGER
#define INCLUDED_GAMESTATEMANAGER

#include <SFML\Graphics.hpp>
#include <vector>

class GameState;

class GameStateManager {
public:
	GameStateManager();
	void setState(int state);
	void update();
	void draw(sf::RenderWindow* window);
	void handleInputs(sf::Event* events);
	int getCurrState();
	static enum states {
		MENUSTATE,
		LEVELSTATE,
	};
private:
	typedef std::vector<GameState*> GameStates;
	GameStates gameStates;
	int currentState;

};

#endif