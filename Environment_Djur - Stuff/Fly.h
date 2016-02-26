#ifndef INCLUDED_FLY
#define INCLUDED_FLY

#include "SFML\Graphics.hpp"

class Fly
{
public:
	Fly(float x, float y);
	void init();
	void update();
	void draw(sf::RenderWindow *window);
private:
	float x;
	float y;
	float velX;
	float velY;
	bool facingRight;

	sf::Clock clock;
	sf::Time time;

	sf::Texture tFly;
	sf::Sprite sFly;

	int timeX;
	int timeY;

	float vX;
	float vY;
};

#endif