#include "Butterfly.h"
#include "Images.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

IntRect rButterfly;

Butterfly::Butterfly(float x, float y, int frameH) :
x(x),
y(y),
velX(-1),
velY(0),
animeTimer(0),
frameW(0),
frameH(frameH),
facingRight(false),
time(0)
{
	init();
}

void Butterfly::init()
{
	//tButterfly.loadFromFile("Resources/Sprites/butterflies_32px.png");
	tButterfly = Images::getTexture(Images::img::BUTTERFLY);
	rButterfly = IntRect(0, 0, 32, 32);
	sButterfly.setTexture(tButterfly);
	sButterfly.setPosition(x, y);
	sButterfly.setOrigin(16, 16);
}

void Butterfly::update()
{
	// move
	time++;
	if (time >= (rand() % 350) + 300)
	{
		velX *= -1;
		time = 0;
	}

	// animation
	animeTimer++;
	if (animeTimer == 5)
	{
		animeTimer = 0;
		frameW++;
	}

	if (frameW > 11) frameW = 0;

	bool tempFacing = facingRight;

	if (velX > 0) facingRight = true;
	if (velX < 0) facingRight = false;

	if (tempFacing != facingRight) sButterfly.scale(-1.f, 1.f);

	rButterfly.left = frameW * 32;
	rButterfly.top = frameH * 32;
	sButterfly.setTextureRect(rButterfly);

	sButterfly.move(velX, velY);
}

void Butterfly::draw(RenderWindow *window)
{
	window->draw(sButterfly, BlendAlpha);
}