#include "Bunny.h"

using namespace sf;

Texture tBunny;
Sprite sBunny;
IntRect rBunny;

Bunny::Bunny() :
x(400),
y(70),
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
	tBunny.loadFromFile("Resources/Sprites/bunnyOff2.png");
	rBunny = IntRect(0, 0, 350, 256);
	sBunny.setTexture(tBunny);
	sBunny.setTextureRect(rBunny);
	sBunny.setPosition(x, y);
	sBunny.setOrigin(175, 128);
}

void Bunny::update()
{
	if (triggered)
	{
		sectionTimer++;
		if (sectionTimer == 1) currentTrigger++;
		else if (sectionTimer < 40) velX = -10;
		//else if (sectionTimer == 50)
		//{
		//	velY = -17;
		//	gravity = true;
		//}
		else if (sectionTimer < 200)
		{
			velX = -10;
		}
		//else if (sectionTimer < 130)
		//{
		//	gravity = false;
		//	velX = -4;
		//	velY = 0;
		//}
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
	if (animeTimer == 3)
	{
		animeTimer = 0;
		frameW++;
	}

	if (velX == 0) frameH = 0;
	else frameH = 1;

	if (frameW > 11) frameW = 0;

	bool tempFacing = facingRight;

	if (velX > 0) facingRight = true;
	if (velX < 0) facingRight = false;

	if (tempFacing != facingRight) sBunny.scale(-1.f, 1.f);

	rBunny.left = frameW * 350;
	rBunny.top = frameH * 256;
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