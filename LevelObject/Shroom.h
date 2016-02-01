#ifndef INCLUDED_SHROOM
#define INCLUDED_SHROOM

#include "SFML\Graphics.hpp"

class Shroom
{
public:
	Shroom(int x, int y, int bounce);
	void init();
	void update();
	void draw(sf::RenderWindow* window);
	sf::Sprite getSprite();
	int getBounce();
	void setUsed(bool b);
private:
	int x;
	int y;
	int bounce;
	int animeTimer;
	int frameW;
	bool used;
};

#endif