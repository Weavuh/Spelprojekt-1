#include "Dog.h"

using namespace sf;

Texture tDog;
Sprite sDog;
IntRect rDog;

Dog::Dog() :
x(1500),
y(80),
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

void Dog::init()
{
	tDog.loadFromFile("Resources/Dog.png");
	rDog = IntRect(0, 0, 512, 512);
	sDog.setTexture(tDog);
	sDog.setTextureRect(rDog);
	sDog.setPosition(x, y);
	sDog.setOrigin(256, 256);
}

void Dog::update()
{
	if (triggered)
	{
		sectionTimer++;
		if (sectionTimer == 1) currentTrigger++;
		else if (sectionTimer < 10) /*velX = -2,*/ velY = -8;
		//else if (sectionTimer == 50)
		//{
		//	velY = -17;
		//	gravity = true;
		//}
		else if (y < -15)
		{
			velY = +8;
		}
		//else if (sectionTimer < 130)
		//{
		//	gravity = false;
		//	velX = -4;
		//	velY = 0;
		//}
		else
		{
			sectionTimer = 0;
			/*sDog.scale(0.5 + velY, 0.5 + velY);*/
		}
	}


	if (gravity) velY += 0.7;

	x += velX;
	y += velY;

	sDog.setPosition(x, y);

	/*animeTimer++;
	if (animeTimer == 3)
	{
	animeTimer = 0;
	frameW++;
	}*/

	/*if (velX == 0) frameH = 0;
	else frameH = 1;*/

	/*if (frameW > 11) frameW = 0;*/

	bool tempFacing = facingRight;

	if (velX > 0) facingRight = true;
	if (velX < 0) facingRight = false;

	if (tempFacing != facingRight) sDog.scale(-1.f, 1.f);

	rDog.left = frameW * 512;
	rDog.top = frameH * 512;
	sDog.setTextureRect(rDog);
}

void Dog::draw(sf::RenderWindow* window)
{
	window->draw(sDog);
}

int Dog::getCurrentTrigger()
{
	return currentTrigger;
}

void Dog::setTriggered(bool b)
{
	triggered = b;
}