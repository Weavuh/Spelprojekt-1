#include "Toucan.h"

using namespace sf;

IntRect rToucan;

Toucan::Toucan() :
x(1200),
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

void Toucan::init()
{
	tToucan.loadFromFile("Resources/Sprites/toucan.png");
	rToucan = IntRect(0, 0, 512, 512);
	sToucan.setTexture(tToucan);
	sToucan.setTextureRect(rToucan);
	sToucan.setPosition(x, y);
	sToucan.setOrigin(256, 256);
}

void Toucan::update()
{
	sToucan.setPosition(x, y);
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

	if (tempFacing != facingRight) sToucan.scale(-1.f, 1.f);

	rToucan.left = frameW * 512;
	rToucan.top = frameH * 512;
	sToucan.setTextureRect(rToucan);
}

void Toucan::draw(sf::RenderWindow* window)
{
	window->draw(sToucan);
}