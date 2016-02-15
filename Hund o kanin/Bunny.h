#ifndef INCLUDED_BUNNY
#define INCLUDED_BUNNY

#include "SFML\Graphics.hpp"

class Bunny
{
public:
	Bunny();
	void init();
	void update();
	void draw(sf::RenderWindow* window);
	int getCurrentTrigger();
	void setTriggered(bool b);
private:
	float x;
	float y;
	float velX;
	float velY;
	int animeTimer;
	int frameW;
	int frameH;
	bool facingRight;
	int currentTrigger;
	bool triggered;
	int sectionTimer;
	bool gravity;
};

#endif