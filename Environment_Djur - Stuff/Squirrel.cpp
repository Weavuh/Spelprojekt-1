#include "Squirrel.h"

using namespace sf;

IntRect rSquirrel;

Squirrel::Squirrel() :
x(700),
y(-50),
velX(0),
velY(0),
animeTimer(0),
frameW(0),
frameH(1),
currentTrigger(0),
triggered(false),
sectionTimer(0),
gravity(0),
facingRight(false)
{
	init();
}

void Squirrel::init()
{
	tSquirrel.loadFromFile("Resources/Sprites/squirrel.png");
	rSquirrel = IntRect(0, 0, 512, 256);
	sSquirrel.setTexture(tSquirrel);
	sSquirrel.setTextureRect(rSquirrel);
	sSquirrel.setPosition(x, y);
	sSquirrel.setOrigin(256, 128);
}

void Squirrel::update()
{
	sSquirrel.setPosition(x, y);
	animeTimer++;
	if (animeTimer == 5)
	{
		animeTimer = 0;
		frameW++;
	}

	/*if (velX == 0) frameH = 0;
	else frameH = 1;*/

	//if (frameW > 0 && frameH == 0) frameW = 0;
	if (frameW > 11) frameW = 0;

	bool tempFacing = facingRight;

	if (velX > 0) facingRight = true;
	if (velX < 0) facingRight = false;

	if (tempFacing != facingRight) sSquirrel.scale(-1.f, 1.f);

	rSquirrel.left = frameW * 512;
	rSquirrel.top = frameH * 256;
	sSquirrel.setTextureRect(rSquirrel);
}

void Squirrel::draw(sf::RenderWindow* window)
{
	window->draw(sSquirrel);
}