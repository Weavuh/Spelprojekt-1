#ifndef INCLUDED_TOUCAN
#define INCLUDED_TOUCAN

#include "SFML\Graphics.hpp"

class Toucan
{
public:
	Toucan();
	void init();
	void update();
	void draw(sf::RenderWindow* window);
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
	sf::Texture tToucan;
	sf::Sprite sToucan;
};

#endif