#ifndef INCLUDED_BUTTERFLY
#define INCLUDED_BUTTERFLY

#include "SFML\Graphics.hpp"

class Butterfly
{
public:
	Butterfly(float x, float y, int frameH);
	void init();
	void update();
	void draw(sf::RenderWindow *window);
private:
	float x;
	float y;
	float velX;
	float velY;
	int animeTimer;
	int frameW;
	int frameH;
	int time;

	sf::Texture tButterfly;
	sf::Sprite sButterfly;
	bool facingRight;
};

#endif