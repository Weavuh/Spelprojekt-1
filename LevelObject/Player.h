#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER

#include <SFML\Graphics.hpp>

class Player
{
public:
	Player();
	void init();
	void update();
	void draw(sf::RenderWindow* window);
	void handleInputs(sf::Event* events);
private:
	float x;
	float velX;
	float y;
	float velY;
	float accY;
	bool jumping;
	bool canJump;
	int animeTimer;
	int frameW;
	int frameH;
	bool facingRight;
};

#endif