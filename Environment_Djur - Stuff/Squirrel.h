#ifndef INCLUDED_SQUIRREL
#define INCLUDED_SQUIRREL

#include "SFML\Graphics.hpp"

class Squirrel
{
public:
	Squirrel();
	void init();
	void update();
	void draw(sf::RenderWindow* window);
	void jdjvhutgfjvjhdgbkbbvxvgfvfkbh();
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
	sf::Texture tSquirrel;
	sf::Sprite sSquirrel;
};

#endif