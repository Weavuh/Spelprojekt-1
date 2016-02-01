#include "Bunny.h"

using namespace sf;

Texture tBunny;
Sprite sBunny;
IntRect rBunny;

Bunny::Bunny() :
x(-400),
y(625),
velX(0),
velY(0),
animeTimer(0),
frameW(0),
frameH(0),
currentTrigger(0),
triggered(false),
sectionTimer(0),
gravity(0),
facingRight(false)
{
	init();
}

void Bunny::init()
{
	tBunny.loadFromFile("Resources/bunny.png");
	rBunny = IntRect(0, 0, 90, 100);
	sBunny.setTexture(tBunny);
	sBunny.setTextureRect(rBunny);
	sBunny.setPosition(x, y);
	sBunny.setOrigin(45, 50);
}

void Bunny::update()
{
	if (triggered)
	{
		sectionTimer++;
		if (sectionTimer == 1) currentTrigger++;
		else if (sectionTimer < 40) velX = -4;
		else if (sectionTimer == 50)
		{
			velY = -17;
			gravity = true;
		}
		else if (sectionTimer < 88)
		{
			velX = -3;
		}
		else if (sectionTimer < 130)
		{
			gravity = false;
			velX = -4;
			velY = 0;
		}
		else
		{
			velX = 0;
			triggered = false;
		}
	}

	if (gravity) velY += 0.7;

	x += velX;
	y += velY;

	sBunny.setPosition(x, y);

	animeTimer++;
	if (animeTimer == 10)
	{
		animeTimer = 0;
		frameW++;
	}

	if (velY == 0) frameH = 0;
	else frameH = 1;

	if (frameW > 2) frameW = 0;

	bool tempFacing = facingRight;

	if (velX > 0) facingRight = true;
	if (velX < 0) facingRight = false;

	if (tempFacing != facingRight) sBunny.scale(-1.f, 1.f);

	rBunny.left = frameW * 90;
	rBunny.top = frameH * 100;
	sBunny.setTextureRect(rBunny);
}

void Bunny::draw(sf::RenderWindow* window)
{
	window->draw(sBunny);
}

int Bunny::getCurrentTrigger()
{
	return currentTrigger;
}

void Bunny::setTriggered(bool b)
{
	triggered = b;
}