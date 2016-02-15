#ifndef INCLUDED_DOG
#define INCLUDED_DOG

#include "SFML\Graphics.hpp"

class Dog
{
public:
	Dog();
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