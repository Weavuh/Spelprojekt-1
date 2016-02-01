#include "Shroom.h"

using namespace sf;

Texture tShroom;
Sprite sShroom;
IntRect rShroom;

Shroom::Shroom(int x, int y, int bounce) :
x(x),
y(y),
bounce(bounce),
animeTimer(0),
frameW(0),
used(false)
{
	init();
}

void Shroom::init()
{
	tShroom.loadFromFile("Resources/shroom.png");
	rShroom = IntRect(0, 0, 100, 100);
	sShroom.setTexture(tShroom);
	sShroom.setTextureRect(rShroom);
	sShroom.setPosition(x, y);
	sShroom.setOrigin(50, 50);
}

void Shroom::update()
{
	
	if (used) animeTimer++;
	if (animeTimer == 15)
	{
		animeTimer = 0;
		frameW++;
	}

	if (frameW > 3)
	{
		used = false;
		frameW = 0;
	}

	rShroom.left = frameW * 100;
	sShroom.setTextureRect(rShroom);
}

void Shroom::draw(sf::RenderWindow* window)
{
	window->draw(sShroom);
}

Sprite Shroom::getSprite()
{
	return sShroom;
}

int Shroom::getBounce()
{
	return bounce;
}

void Shroom::setUsed(bool b)
{
	used = b;
}